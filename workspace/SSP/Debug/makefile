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
all: SSP.axf

dependents:
	-cd /home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug && $(MAKE) clean all
	-cd /home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug && $(MAKE) clean all

# Tool invocations
SSP.axf: $(OBJS) $(USER_OBJS) /home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a /home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug" -L"/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug" -L"/home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/src" -Xlinker -Map="SSP.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "SSP_Debug.ld" -o "SSP.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) SSP.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "SSP.axf"; # arm-none-eabi-objcopy -O binary "SSP.axf" "SSP.bin" ; checksum -p LPC11U14_201 -d "SSP.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a:
/home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a:

-include ../makefile.targets
