################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MKL46_Driver/Kl46_timer.c \
../MKL46_Driver/adc.c \
../MKL46_Driver/clock.c \
../MKL46_Driver/flash.c \
../MKL46_Driver/gpio.c \
../MKL46_Driver/pit.c \
../MKL46_Driver/port.c \
../MKL46_Driver/sim.c \
../MKL46_Driver/uart.c 

C_DEPS += \
./MKL46_Driver/Kl46_timer.d \
./MKL46_Driver/adc.d \
./MKL46_Driver/clock.d \
./MKL46_Driver/flash.d \
./MKL46_Driver/gpio.d \
./MKL46_Driver/pit.d \
./MKL46_Driver/port.d \
./MKL46_Driver/sim.d \
./MKL46_Driver/uart.d 

OBJS += \
./MKL46_Driver/Kl46_timer.o \
./MKL46_Driver/adc.o \
./MKL46_Driver/clock.o \
./MKL46_Driver/flash.o \
./MKL46_Driver/gpio.o \
./MKL46_Driver/pit.o \
./MKL46_Driver/port.o \
./MKL46_Driver/sim.o \
./MKL46_Driver/uart.o 


# Each subdirectory must supply rules for building sources it contributes
MKL46_Driver/%.o: ../MKL46_Driver/%.c MKL46_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\source" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\MKL46_Driver" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\CMSIS" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\startup" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\debugger" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\middleware" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MKL46_Driver

clean-MKL46_Driver:
	-$(RM) ./MKL46_Driver/Kl46_timer.d ./MKL46_Driver/Kl46_timer.o ./MKL46_Driver/adc.d ./MKL46_Driver/adc.o ./MKL46_Driver/clock.d ./MKL46_Driver/clock.o ./MKL46_Driver/flash.d ./MKL46_Driver/flash.o ./MKL46_Driver/gpio.d ./MKL46_Driver/gpio.o ./MKL46_Driver/pit.d ./MKL46_Driver/pit.o ./MKL46_Driver/port.d ./MKL46_Driver/port.o ./MKL46_Driver/sim.d ./MKL46_Driver/sim.o ./MKL46_Driver/uart.d ./MKL46_Driver/uart.o

.PHONY: clean-MKL46_Driver

