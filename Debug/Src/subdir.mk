################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GUI.c \
../Src/main.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/system_stm32f0xx.c \
../Src/t14-math.c \
../Src/t14-ssi.c \
../Src/t14-usb.c \
../Src/usb_device.c \
../Src/usbd_cdc_if.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c 

OBJS += \
./Src/GUI.o \
./Src/main.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/system_stm32f0xx.o \
./Src/t14-math.o \
./Src/t14-ssi.o \
./Src/t14-usb.o \
./Src/usb_device.o \
./Src/usbd_cdc_if.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o 

C_DEPS += \
./Src/GUI.d \
./Src/main.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/system_stm32f0xx.d \
./Src/t14-math.d \
./Src/t14-ssi.d \
./Src/t14-usb.d \
./Src/usb_device.d \
./Src/usbd_cdc_if.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -ggdb -DDEBUG -DSTM32F072xB -DUSE_FULL_ASSERT -DUSE_STM32 -DSTM32F072 -DHSE_VALUE=8000000 -DEMB_FLASH -I"C:\C_workspace\ARM_F0_HAL\Drivers\CMSIS\Device\ST\STM32F0xx\Include" -I"C:\C_workspace\ARM_F0_HAL\Drivers\CMSIS\Include" -I"C:\C_workspace\ARM_F0_HAL\Drivers\STM32F0xx_HAL_Driver\Inc" -I"C:\C_workspace\ARM_F0_HAL\Inc" -I"C:\C_workspace\ARM_F0_HAL\Middlewares\ST\STM32_USB_Device_Library\Class\CDC\Inc" -I"C:\C_workspace\ARM_F0_HAL\Middlewares\ST\STM32_USB_Device_Library\Core\Inc" -I"C:\C_workspace\ARM_F0_HAL\FT801\inc" -I"C:\MinGW\include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


