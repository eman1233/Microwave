################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../usart_driver.c 

OBJS += \
./main.o \
./usart_driver.o 

C_DEPS += \
./main.d \
./usart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\1\NTI\AVR\AVR\RTOS\FreeRTOS\FreeRTOS\Inc" -I"E:\1\NTI\AVR\AVR\RTOS\HAL" -I"E:\1\NTI\AVR\AVR\RTOS\HAL\button" -I"E:\1\NTI\AVR\AVR\RTOS\HAL\Keypad" -I"E:\1\NTI\AVR\AVR\RTOS\HAL\LCD" -I"E:\1\NTI\AVR\AVR\RTOS\HAL\Led" -I"E:\1\NTI\AVR\AVR\RTOS\HAL\motor" -I"E:\1\NTI\AVR\AVR\RTOS\MCAL\GPIO" -I"E:\1\NTI\AVR\AVR\RTOS\MCAL\Timer" -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


