################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../esp8266/esp8266.c 

OBJS += \
./esp8266/esp8266.o 

C_DEPS += \
./esp8266/esp8266.d 


# Each subdirectory must supply rules for building sources it contributes
esp8266/%.o esp8266/%.su esp8266/%.cyclo: ../esp8266/%.c esp8266/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F722xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/home/vikrant/msr_iitd/projects/APMD/esp8266_stm32/esp8266" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-esp8266

clean-esp8266:
	-$(RM) ./esp8266/esp8266.cyclo ./esp8266/esp8266.d ./esp8266/esp8266.o ./esp8266/esp8266.su

.PHONY: clean-esp8266

