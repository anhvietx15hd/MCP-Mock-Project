################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/uart/Src/KL46_uart.c 

C_DEPS += \
./drivers/uart/Src/KL46_uart.d 

OBJS += \
./drivers/uart/Src/KL46_uart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/uart/Src/%.o: ../drivers/uart/Src/%.c drivers/uart/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\drivers\gpio\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\middle\devices\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\drivers\port\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\drivers\timer\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\drivers\uart\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\middle\BIOS\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\source" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\drivers\clock\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\drivers\flash\Inc" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\CMSIS" -I"F:\EMBEDDED\MCP\Programming\LeHungViet_MockPRJ\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers-2f-uart-2f-Src

clean-drivers-2f-uart-2f-Src:
	-$(RM) ./drivers/uart/Src/KL46_uart.d ./drivers/uart/Src/KL46_uart.o

.PHONY: clean-drivers-2f-uart-2f-Src

