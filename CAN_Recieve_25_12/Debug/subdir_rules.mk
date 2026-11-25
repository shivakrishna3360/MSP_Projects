################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/MSP/CAN_Recieve_25_12" --include_path="D:/MSP/CAN_Recieve_25_12/Debug" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/ti/net/bsd" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/ti/posix/ccs" --include_path="C:/ti/FreeRTOSv10.1.1/FreeRTOS/Source/include" --include_path="C:/ti/FreeRTOSv10.1.1/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="D:/MSP/freertos_builds_MSP_EXP432E401Y_release_ccs" --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=none --define=DeviceFamily_MSP432E4 --define=__MSP432E401Y__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/MSP/CAN_Recieve_25_12/Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-2112310129: ../cangpiotxrx.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1010/ccs/utils/sysconfig_1.5.0/sysconfig_cli.bat" -s "C:/ti/simplelink_msp432e4_sdk_4_20_00_12/.metadata/product.json" -o "syscfg" --compiler ccs "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-2112310129 ../cangpiotxrx.syscfg
syscfg/ti_drivers_config.h: build-2112310129
syscfg/ti_utils_build_linker.cmd.exp: build-2112310129
syscfg/syscfg_c.rov.xs: build-2112310129
syscfg/: build-2112310129

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/MSP/CAN_Recieve_25_12" --include_path="D:/MSP/CAN_Recieve_25_12/Debug" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/ti/net/bsd" --include_path="C:/ti/simplelink_msp432e4_sdk_4_20_00_12/source/ti/posix/ccs" --include_path="C:/ti/FreeRTOSv10.1.1/FreeRTOS/Source/include" --include_path="C:/ti/FreeRTOSv10.1.1/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="D:/MSP/freertos_builds_MSP_EXP432E401Y_release_ccs" --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=none --define=DeviceFamily_MSP432E4 --define=__MSP432E401Y__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="D:/MSP/CAN_Recieve_25_12/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


