################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/4lab_pmu_fib/driver/adc.c \
../src/4lab_pmu_fib/driver/can.c \
../src/4lab_pmu_fib/driver/clkconfig.c \
../src/4lab_pmu_fib/driver/crp.c \
../src/4lab_pmu_fib/driver/debug_printf.c \
../src/4lab_pmu_fib/driver/gpio.c \
../src/4lab_pmu_fib/driver/i2c.c \
../src/4lab_pmu_fib/driver/i2cslave.c \
../src/4lab_pmu_fib/driver/lpc_swu.c \
../src/4lab_pmu_fib/driver/rs485.c \
../src/4lab_pmu_fib/driver/small_gpio.c \
../src/4lab_pmu_fib/driver/ssp.c \
../src/4lab_pmu_fib/driver/timer16.c \
../src/4lab_pmu_fib/driver/timer32.c \
../src/4lab_pmu_fib/driver/uart.c \
../src/4lab_pmu_fib/driver/wdt.c 

OBJS += \
./src/4lab_pmu_fib/driver/adc.o \
./src/4lab_pmu_fib/driver/can.o \
./src/4lab_pmu_fib/driver/clkconfig.o \
./src/4lab_pmu_fib/driver/crp.o \
./src/4lab_pmu_fib/driver/debug_printf.o \
./src/4lab_pmu_fib/driver/gpio.o \
./src/4lab_pmu_fib/driver/i2c.o \
./src/4lab_pmu_fib/driver/i2cslave.o \
./src/4lab_pmu_fib/driver/lpc_swu.o \
./src/4lab_pmu_fib/driver/rs485.o \
./src/4lab_pmu_fib/driver/small_gpio.o \
./src/4lab_pmu_fib/driver/ssp.o \
./src/4lab_pmu_fib/driver/timer16.o \
./src/4lab_pmu_fib/driver/timer32.o \
./src/4lab_pmu_fib/driver/uart.o \
./src/4lab_pmu_fib/driver/wdt.o 

C_DEPS += \
./src/4lab_pmu_fib/driver/adc.d \
./src/4lab_pmu_fib/driver/can.d \
./src/4lab_pmu_fib/driver/clkconfig.d \
./src/4lab_pmu_fib/driver/crp.d \
./src/4lab_pmu_fib/driver/debug_printf.d \
./src/4lab_pmu_fib/driver/gpio.d \
./src/4lab_pmu_fib/driver/i2c.d \
./src/4lab_pmu_fib/driver/i2cslave.d \
./src/4lab_pmu_fib/driver/lpc_swu.d \
./src/4lab_pmu_fib/driver/rs485.d \
./src/4lab_pmu_fib/driver/small_gpio.d \
./src/4lab_pmu_fib/driver/ssp.d \
./src/4lab_pmu_fib/driver/timer16.d \
./src/4lab_pmu_fib/driver/timer32.d \
./src/4lab_pmu_fib/driver/uart.d \
./src/4lab_pmu_fib/driver/wdt.d 


# Each subdirectory must supply rules for building sources it contributes
src/4lab_pmu_fib/driver/%.o: ../src/4lab_pmu_fib/driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"Z:\school\3360\workspace\LPC11Uxx_Driver_Lib" -I"Z:\school\3360\workspace\CMSISv2p00_LPC11Uxx\inc" -I"Z:\school\3360\workspace\LPC11Uxx_Driver_Lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


