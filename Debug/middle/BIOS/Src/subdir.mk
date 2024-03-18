################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middle/BIOS/Src/KL46_bios.c \
../middle/BIOS/Src/SREC_parse.c 

C_DEPS += \
./middle/BIOS/Src/KL46_bios.d \
./middle/BIOS/Src/SREC_parse.d 

OBJS += \
./middle/BIOS/Src/KL46_bios.o \
./middle/BIOS/Src/SREC_parse.o 


# Each subdirectory must supply rules for building sources it contributes
middle/BIOS/Src/%.o: ../middle/BIOS/Src/%.c middle/BIOS/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\gpio\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\middle\devices\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\port\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\timer\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\uart\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\middle\BIOS\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\source" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\clock\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\drivers\flash\Inc" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\CMSIS" -I"D:\MCU_E\workplace\mock\MCP-Mock-Project\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-middle-2f-BIOS-2f-Src

clean-middle-2f-BIOS-2f-Src:
	-$(RM) ./middle/BIOS/Src/KL46_bios.d ./middle/BIOS/Src/KL46_bios.o ./middle/BIOS/Src/SREC_parse.d ./middle/BIOS/Src/SREC_parse.o

.PHONY: clean-middle-2f-BIOS-2f-Src

