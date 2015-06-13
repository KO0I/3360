################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DiskImg.c \
../src/comp_lpc11uxx_usbdesc.c \
../src/cr_startup_lpc11u.c \
../src/dfu_lpc11uxx_usbdesc.c \
../src/hid_lpc11uxx_usbdesc.c \
../src/lpc11uxx_usbd_dfu.c \
../src/lpc11uxx_usbd_hid.c \
../src/lpc11uxx_usbd_msc_mem.c \
../src/main.c \
../src/sbl_iap.c 

OBJS += \
./src/DiskImg.o \
./src/comp_lpc11uxx_usbdesc.o \
./src/cr_startup_lpc11u.o \
./src/dfu_lpc11uxx_usbdesc.o \
./src/hid_lpc11uxx_usbdesc.o \
./src/lpc11uxx_usbd_dfu.o \
./src/lpc11uxx_usbd_hid.o \
./src/lpc11uxx_usbd_msc_mem.o \
./src/main.o \
./src/sbl_iap.o 

C_DEPS += \
./src/DiskImg.d \
./src/comp_lpc11uxx_usbdesc.d \
./src/cr_startup_lpc11u.d \
./src/dfu_lpc11uxx_usbdesc.d \
./src/hid_lpc11uxx_usbdesc.d \
./src/lpc11uxx_usbd_dfu.d \
./src/lpc11uxx_usbd_hid.d \
./src/lpc11uxx_usbd_msc_mem.d \
./src/main.d \
./src/sbl_iap.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DNDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/home/patrick/school/ddl_3360/workspace/CMSISv2p00_LPC11Uxx/inc" -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


