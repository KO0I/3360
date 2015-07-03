################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/4lab_pmu_fib/cmsis/core_cm0.c \
../src/4lab_pmu_fib/cmsis/system_LPC11xx.c 

OBJS += \
./src/4lab_pmu_fib/cmsis/core_cm0.o \
./src/4lab_pmu_fib/cmsis/system_LPC11xx.o 

C_DEPS += \
./src/4lab_pmu_fib/cmsis/core_cm0.d \
./src/4lab_pmu_fib/cmsis/system_LPC11xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/4lab_pmu_fib/cmsis/%.o: ../src/4lab_pmu_fib/cmsis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"Z:\school\3360\workspace\LPC11Uxx_Driver_Lib" -I"Z:\school\3360\workspace\CMSISv2p00_LPC11Uxx\inc" -I"Z:\school\3360\workspace\LPC11Uxx_Driver_Lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


