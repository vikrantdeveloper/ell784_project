################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Include/common.c 

OBJS += \
./Include/common.o 

C_DEPS += \
./Include/common.d 


# Each subdirectory must supply rules for building sources it contributes
Include/%.o Include/%.su Include/%.cyclo: ../Include/%.c Include/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F722xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/home/vikrant/msr_iitd/projects/APMD/esp8266_stm32/esp8266" -I"/home/vikrant/msr_iitd/projects/APMD/esp8266_stm32/DTH11" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Include

clean-Include:
	-$(RM) ./Include/common.cyclo ./Include/common.d ./Include/common.o ./Include/common.su

.PHONY: clean-Include

