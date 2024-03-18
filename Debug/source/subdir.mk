################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LeHungViet_MockPRJ.c \
../source/mtb.c 

C_DEPS += \
./source/LeHungViet_MockPRJ.d \
./source/mtb.d 

OBJS += \
./source/LeHungViet_MockPRJ.o \
./source/mtb.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\gpio\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\middle\devices\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\port\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\timer\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\uart\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\middle\BIOS\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\source" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\clock\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\flash\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\CMSIS" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/LeHungViet_MockPRJ.d ./source/LeHungViet_MockPRJ.o ./source/mtb.d ./source/mtb.o

.PHONY: clean-source

