################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/4lab_pmu_fib/startup/subdir.mk
-include src/4lab_pmu_fib/src/subdir.mk
-include src/4lab_pmu_fib/driver/subdir.mk
-include src/4lab_pmu_fib/cmsis/subdir.mk
-include src/4lab_pmu_fib/Debug/startup/subdir.mk
-include src/4lab_pmu_fib/Debug/src/subdir.mk
-include src/4lab_pmu_fib/Debug/driver/subdir.mk
-include src/4lab_pmu_fib/Debug/cmsis/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 5lab_UART_BT.axf

dependents:
	-cd Z:/school/3360/workspace/CMSISv2p00_LPC11Uxx/Debug && $(MAKE) clean all
	-cd Z:/school/3360/workspace/LPC11Uxx_Driver_Lib/Debug && $(MAKE) clean all

# Tool invocations
5lab_UART_BT.axf: $(OBJS) $(USER_OBJS) Z:/school/3360/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a Z:/school/3360/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"Z:\school\3360\workspace\LPC11Uxx_Driver_Lib\Debug" -L"Z:\school\3360\workspace\CMSISv2p00_LPC11Uxx\Debug" -Xlinker -Map="5lab_UART_BT.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "5lab_UART_BT_Debug.ld" -o "5lab_UART_BT.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) 5lab_UART_BT.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "5lab_UART_BT.axf"; # arm-none-eabi-objcopy -O binary "5lab_UART_BT.axf" "5lab_UART_BT.bin" ; checksum -p LPC11U14_201 -d "5lab_UART_BT.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
Z:/school/3360/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a:
Z:/school/3360/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a:

-include ../makefile.targets
