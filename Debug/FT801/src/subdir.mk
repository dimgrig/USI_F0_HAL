################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FT801/src/FT_App.c \
../FT801/src/FT_CoPro_Cmds.c \
../FT801/src/FT_Gpu_Hal.c 

OBJS += \
./FT801/src/FT_App.o \
./FT801/src/FT_CoPro_Cmds.o \
./FT801/src/FT_Gpu_Hal.o 

C_DEPS += \
./FT801/src/FT_App.d \
./FT801/src/FT_CoPro_Cmds.d \
./FT801/src/FT_Gpu_Hal.d 


# Each subdirectory must supply rules for building sources it contributes
FT801/src/%.o: ../FT801/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -ggdb -DDEBUG -DSTM32F072xB -DUSE_FULL_ASSERT -DUSE_STM32 -DSTM32F072 -DHSE_VALUE=8000000 -DEMB_FLASH -I"C:\C_workspace\ARM_F0_HAL\Drivers\CMSIS\Device\ST\STM32F0xx\Include" -I"C:\C_workspace\ARM_F0_HAL\Drivers\CMSIS\Include" -I"C:\C_workspace\ARM_F0_HAL\Drivers\STM32F0xx_HAL_Driver\Inc" -I"C:\C_workspace\ARM_F0_HAL\Inc" -I"C:\C_workspace\ARM_F0_HAL\Middlewares\ST\STM32_USB_Device_Library\Class\CDC\Inc" -I"C:\C_workspace\ARM_F0_HAL\Middlewares\ST\STM32_USB_Device_Library\Core\Inc" -I"C:\C_workspace\ARM_F0_HAL\FT801\inc" -I"C:\MinGW\include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


