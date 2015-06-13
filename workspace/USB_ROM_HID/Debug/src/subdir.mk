################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc11u.c \
../src/hid_lpc11uxx_usbdesc.c \
../src/lpc11uxx_usbd_hid.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc11u.o \
./src/hid_lpc11uxx_usbdesc.o \
./src/lpc11uxx_usbd_hid.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc11u.d \
./src/hid_lpc11uxx_usbdesc.d \
./src/lpc11uxx_usbd_hid.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/inc" -I"/home/patrick/school/ddl_3360/workspace/USB_ROM_HID/inc" -I"/home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib" -I"/home/patrick/school/ddl_3360/workspace/LPC11Uxx_Driver_Lib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


