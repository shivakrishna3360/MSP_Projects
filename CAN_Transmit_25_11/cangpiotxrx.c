/*
 *  ======== cangpiotxrx.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* POSIX Header files */
#include <pthread.h>

/* RTOS Header files */
#include <FreeRTOS.h>
#include <task.h>

/* Driver Header files */
#include <ti/drivers/CAN.h>
#include <ti/drivers/GPIO.h>
#include <ti/display/Display.h>

/* Example/Board Header files */
#include "ti_drivers_config.h"

#define THREADSTACKSIZE (1024)

static CAN_Handle can;
static Display_Handle display;
static pthread_mutex_t canMutex;

/*
 * ======== txTask1 ========
 * Periodically transmits a CAN frame with ID 0x101.
 */
void *txTask1(void *arg0)
{
    uint8_t counter = 0;

    while (1) {
        CAN_Frame canFrame = {0};
        canFrame.id = 0x101;
        canFrame.dlc = 1;
        canFrame.data[0] = counter++;

        pthread_mutex_lock(&canMutex);
        CAN_write(can, &canFrame, sizeof(canFrame));
        Display_print2(display, 0, 0, "Task 1 sent ID: 0x%03x | Data: %d",
                       canFrame.id, canFrame.data[0]);
        pthread_mutex_unlock(&canMutex);

        GPIO_toggle(CONFIG_GPIO_LED_0);

        /* Transmit every 1000 ms */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*
 * ======== txTask2 ========
 * Periodically transmits a CAN frame with ID 0x102.
 */
void *txTask2(void *arg0)
{
    uint8_t counter = 0;

    while (1) {
        CAN_Frame canFrame = {0};
        canFrame.id = 0x102;
        canFrame.dlc = 1;
        canFrame.data[0] = counter++;

        pthread_mutex_lock(&canMutex);
        CAN_write(can, &canFrame, sizeof(canFrame));
        Display_print2(display, 0, 0, "Task 2 sent ID: 0x%03x | Data: %d",
                       canFrame.id, canFrame.data[0]);
        pthread_mutex_unlock(&canMutex);

        /* Transmit every 1500 ms */
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

/*
 * ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    pthread_t           thread1, thread2;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;

    /* Call driver init functions */
    GPIO_init();
    CAN_init();
    Display_init();

    /* Open CAN instance (default params since RX filtering is not needed) */
    CAN_Params canParams;
    CAN_Params_init(&canParams);
    can = CAN_open(CONFIG_CAN_0, &canParams);
    if (can == NULL) {
        while (1);
    }

    /* Open Display instance for UART */
    Display_Params displayParams;
    Display_Params_init(&displayParams);
    display = Display_open(Display_Type_UART, &displayParams);

    Display_print0(display, 0, 0, "== CAN Dual-Task Transmitter Started ==");

    /* Configure LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);

    /* Initialize mutex to protect shared CAN and Display handles */
    if (pthread_mutex_init(&canMutex, NULL) != 0) {
        Display_print0(display, 0, 0, "Error creating mutex");
        while (1);
    }

    /* Set common thread attributes */
    pthread_attr_init(&attrs);
    priParam.sched_priority = 1;
    pthread_attr_setschedparam(&attrs, &priParam);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);

    /* Create Task 1 (ID: 0x101) */
    retc = pthread_create(&thread1, &attrs, txTask1, NULL);
    if (retc != 0) {
        while (1);
    }

    /* Create Task 2 (ID: 0x102) */
    retc = pthread_create(&thread2, &attrs, txTask2, NULL);
    if (retc != 0) {
        while (1);
    }

    /* Exit mainThread; FreeRTOS scheduler keeps txTask1 and txTask2 running */
    return (NULL);
}
