################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/GPIO_Driver.c \
../Drivers/Src/RCC_Driver.c 

OBJS += \
./Drivers/Src/GPIO_Driver.o \
./Drivers/Src/RCC_Driver.o 

C_DEPS += \
./Drivers/Src/GPIO_Driver.d \
./Drivers/Src/RCC_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411VETx -DSTM32 -DSTM32F4 -DSTM32F411E_DISCO -c -I../Inc -I"C:/Users/sathyan/STM32CubeIDE/workspace_1.18.0/DeviceDrivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/GPIO_Driver.cyclo ./Drivers/Src/GPIO_Driver.d ./Drivers/Src/GPIO_Driver.o ./Drivers/Src/GPIO_Driver.su ./Drivers/Src/RCC_Driver.cyclo ./Drivers/Src/RCC_Driver.d ./Drivers/Src/RCC_Driver.o ./Drivers/Src/RCC_Driver.su

.PHONY: clean-Drivers-2f-Src

