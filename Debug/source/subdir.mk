################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MKL46Z4_Project.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/MKL46Z4_Project.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/MKL46Z4_Project.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/MKL46Z4_Project.o: ../source/MKL46Z4_Project.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\MCU_E\workplace\MKL46Z4_Project\source" -I"D:\MCU_E\workplace\MKL46Z4_Project\MKL46_Driver" -I"D:\MCU_E\workplace\MKL46Z4_Project" -I"D:\MCU_E\workplace\MKL46Z4_Project\CMSIS" -I"D:\MCU_E\workplace\MKL46Z4_Project\startup" -I"D:\MCU_E\workplace\MKL46Z4_Project\debugger" -I"D:\MCU_E\workplace\MKL46Z4_Project\SREC" -I"D:\MCU_E\workplace\MKL46Z4_Project\middleware" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\MCU_E\workplace\MKL46Z4_Project\source" -I"D:\MCU_E\workplace\MKL46Z4_Project\MKL46_Driver" -I"D:\MCU_E\workplace\MKL46Z4_Project" -I"D:\MCU_E\workplace\MKL46Z4_Project\CMSIS" -I"D:\MCU_E\workplace\MKL46Z4_Project\startup" -I"D:\MCU_E\workplace\MKL46Z4_Project\debugger" -I"D:\MCU_E\workplace\MKL46Z4_Project\SREC" -I"D:\MCU_E\workplace\MKL46Z4_Project\middleware" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/MKL46Z4_Project.d ./source/MKL46Z4_Project.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

