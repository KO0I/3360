################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/4lab_pmu_fib/startup/cr_startup_lpc11.c 

OBJS += \
./src/4lab_pmu_fib/startup/cr_startup_lpc11.o 

C_DEPS += \
./src/4lab_pmu_fib/startup/cr_startup_lpc11.d 


# Each subdirectory must supply rules for building sources it contributes
src/4lab_pmu_fib/startup/%.o: ../src/4lab_pmu_fib/startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"Z:\school\3360\workspace\LPC11Uxx_Driver_Lib" -I"Z:\school\3360\workspace\CMSISv2p00_LPC11Uxx\inc" -I"Z:\school\3360\workspace\LPC11Uxx_Driver_Lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


