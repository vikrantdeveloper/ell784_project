################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DTH11/dth11.c 

OBJS += \
./DTH11/dth11.o 

C_DEPS += \
./DTH11/dth11.d 


# Each subdirectory must supply rules for building sources it contributes
DTH11/%.o DTH11/%.su DTH11/%.cyclo: ../DTH11/%.c DTH11/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F722xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/home/vikrant/msr_iitd/projects/APMD/esp8266_stm32/esp8266" -I"/home/vikrant/msr_iitd/projects/APMD/esp8266_stm32/DTH11" -I"/home/vikrant/msr_iitd/projects/APMD/esp8266_stm32/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DTH11

clean-DTH11:
	-$(RM) ./DTH11/dth11.cyclo ./DTH11/dth11.d ./DTH11/dth11.o ./DTH11/dth11.su

.PHONY: clean-DTH11

