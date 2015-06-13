################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
all: asm_fibonacci.axf

dependents:
	-cd /home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug && $(MAKE) clean all
	-cd /home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug && $(MAKE) clean all
	-cd /home/patrick/school/ddl_3360/workspace/ADC/Debug && $(MAKE) clean all
	-cd /home/patrick/school/ddl_3360/workspace/UART/Debug && $(MAKE) clean all

# Tool invocations
asm_fibonacci.axf: $(OBJS) $(USER_OBJS) /home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a /home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a /home/patrick/school/ddl_3360/workspace/ADC/Debug/ADC.axf /home/patrick/school/ddl_3360/workspace/UART/Debug/UART.axf
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug" -L"/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug" -L/CMSISv2p00_LPC11uxx/Debug -Xlinker --gc-sections -Xlinker -Map=asm_fibonacci.map -mcpu=cortex-m0 -mthumb -T "asm_fibonacci_Debug.ld" -o "asm_fibonacci.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) asm_fibonacci.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size asm_fibonacci.axf; # arm-none-eabi-objcopy -O ihex asm_fibonacci.axf asm_fibonacci.hex ;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a:
/home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a:
/home/patrick/school/ddl_3360/workspace/ADC/Debug/ADC.axf:
/home/patrick/school/ddl_3360/workspace/UART/Debug/UART.axf:

-include ../makefile.targets
