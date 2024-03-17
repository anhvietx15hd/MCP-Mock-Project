################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/KL46_bios.c \
../middleware/SREC_parse.c \
../middleware/led.c 

C_DEPS += \
./middleware/KL46_bios.d \
./middleware/SREC_parse.d \
./middleware/led.d 

OBJS += \
./middleware/KL46_bios.o \
./middleware/SREC_parse.o \
./middleware/led.o 


# Each subdirectory must supply rules for building sources it contributes
middleware/%.o: ../middleware/%.c middleware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\MCU_E\workplace\MKL46Z4_Project\source" -I"D:\MCU_E\workplace\MKL46Z4_Project\MKL46_Driver" -I"D:\MCU_E\workplace\MKL46Z4_Project" -I"D:\MCU_E\workplace\MKL46Z4_Project\CMSIS" -I"D:\MCU_E\workplace\MKL46Z4_Project\startup" -I"D:\MCU_E\workplace\MKL46Z4_Project\debugger" -I"D:\MCU_E\workplace\MKL46Z4_Project\SREC" -I"D:\MCU_E\workplace\MKL46Z4_Project\middleware" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-middleware

clean-middleware:
	-$(RM) ./middleware/KL46_bios.d ./middleware/KL46_bios.o ./middleware/SREC_parse.d ./middleware/SREC_parse.o ./middleware/led.d ./middleware/led.o

.PHONY: clean-middleware

