################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -ggdb -DDEBUG -DSTM32F072xB -DUSE_FULL_ASSERT -DUSE_STM32 -DSTM32F072 -DHSE_VALUE=8000000 -DEMB_FLASH -I"C:\C_workspace\ARM_F0_HAL\Drivers\CMSIS\Device\ST\STM32F0xx\Include" -I"C:\C_workspace\ARM_F0_HAL\Drivers\CMSIS\Include" -I"C:\C_workspace\ARM_F0_HAL\Drivers\STM32F0xx_HAL_Driver\Inc" -I"C:\C_workspace\ARM_F0_HAL\Inc" -I"C:\C_workspace\ARM_F0_HAL\Middlewares\ST\STM32_USB_Device_Library\Class\CDC\Inc" -I"C:\C_workspace\ARM_F0_HAL\Middlewares\ST\STM32_USB_Device_Library\Core\Inc" -I"C:\C_workspace\ARM_F0_HAL\FT801\inc" -I"C:\MinGW\include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


