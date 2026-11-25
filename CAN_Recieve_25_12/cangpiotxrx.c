/*
 *  ======== cangpiotxrx.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/CAN.h>
#include <ti/drivers/GPIO.h>
#include <ti/display/Display.h>

/* Example/Board Header files */
#include "ti_drivers_config.h"

static CAN_Handle can;
static Display_Handle display;

/*
 * ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();
    CAN_init();
    Display_init();

    /*
     * Configure CAN hardware filter to accept ONLY 0x101 and 0x102:
     *   0x101 = 0b 001 0000 0001
     *   0x102 = 0b 001 0000 0010
     *   -------------------------
     *   Mask  = 0b 111 1111 1100 = 0x7FC (checks top 9 bits, ignores bottom 2)
     */
    CAN_Params canParams;
    CAN_Params_init(&canParams);
    canParams.filterID   = 0x100;
    canParams.filterMask = 0x7FC;

    can = CAN_open(CONFIG_CAN_0, &canParams);
    if (can == NULL) {
        while (1);
    }

    /* Open Display instance for UART */
    Display_Params displayParams;
    Display_Params_init(&displayParams);
    display = Display_open(Display_Type_UART, &displayParams);

    Display_print0(display, 0, 0, "== CAN Receiver Ready (Accepting 0x101 & 0x102) ==");

    /* Configure LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_HIGH);

    CAN_Frame canFrame = {0};

    while (1) {
        /* Blocks until a matching CAN frame arrives */
        if (CAN_read(can, &canFrame, sizeof(canFrame)) == CAN_STATUS_SUCCESS) {
            /* Strictly accept only 0x101 and 0x102 (filters out 0x100 and 0x103) */
            if (canFrame.id == 0x101 || canFrame.id == 0x102) {
                GPIO_toggle(CONFIG_GPIO_LED_0);

                Display_print2(display, 0, 0, "Received ID: 0x%03x | Data[0]: %d",
                               canFrame.id, canFrame.data[0]);
            }
        }
    }
}
