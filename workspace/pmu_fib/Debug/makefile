################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include driver/subdir.mk
-include cmsis/subdir.mk
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
all: pmu_fib.axf

dependents:
	-cd /home/patrick/school/ddl_3360/workspace/pmu/Debug && $(MAKE) clean all

# Tool invocations
pmu_fib.axf: $(OBJS) $(USER_OBJS) /home/patrick/school/ddl_3360/workspace/pmu/Debug/pmu.axf
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map=pmu_fib.map -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "pmu_fib_Debug.ld" -o "pmu_fib.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) pmu_fib.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size pmu_fib.axf; # arm-none-eabi-objcopy -O binary pmu_fib.axf pmu_fib.bin ; checksum -p LPC11U14_201 -d pmu_fib.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/patrick/school/ddl_3360/workspace/pmu/Debug/pmu.axf:

-include ../makefile.targets
