################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/clkconfig.c \
../src/cr_startup_lpc11u.c \
../src/gpio.c \
../src/pmu.c \
../src/pmutest.c \
../src/system_LPC11Uxx.c \
../src/timer16.c 

OBJS += \
./src/clkconfig.o \
./src/cr_startup_lpc11u.o \
./src/gpio.o \
./src/pmu.o \
./src/pmutest.o \
./src/system_LPC11Uxx.o \
./src/timer16.o 

C_DEPS += \
./src/clkconfig.d \
./src/cr_startup_lpc11u.d \
./src/gpio.d \
./src/pmu.d \
./src/pmutest.d \
./src/system_LPC11Uxx.d \
./src/timer16.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc11u.o: ../src/cr_startup_lpc11u.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc11u.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


