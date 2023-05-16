################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := NUCLEO-F401RE_I2C_ADDR_SCANNER
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NUCLEO-F401RE_I2C_ADDR_SCANNER.elf \

MAP_FILES += \
NUCLEO-F401RE_I2C_ADDR_SCANNER.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NUCLEO-F401RE_I2C_ADDR_SCANNER.list \

OBJCOPY_HEX += \
NUCLEO-F401RE_I2C_ADDR_SCANNER.hex \

OBJCOPY_BIN += \
NUCLEO-F401RE_I2C_ADDR_SCANNER.bin \


# All Target
all: main-build

# Main-build Target
main-build: NUCLEO-F401RE_I2C_ADDR_SCANNER.elf secondary-outputs

# Tool invocations
NUCLEO-F401RE_I2C_ADDR_SCANNER.elf NUCLEO-F401RE_I2C_ADDR_SCANNER.map: $(OBJS) $(USER_OBJS) D:\Dai_Hoc\Ki_2_Nam_3\THUC_TAP_CO_SO\BAI_TAP_CUOI_KY\SOURCE_CODE\NUCLEO-F401RE_I2C_ADDR_SCANNER\STM32F401RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "NUCLEO-F401RE_I2C_ADDR_SCANNER.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\Dai_Hoc\Ki_2_Nam_3\THUC_TAP_CO_SO\BAI_TAP_CUOI_KY\SOURCE_CODE\NUCLEO-F401RE_I2C_ADDR_SCANNER\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NUCLEO-F401RE_I2C_ADDR_SCANNER.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO-F401RE_I2C_ADDR_SCANNER.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NUCLEO-F401RE_I2C_ADDR_SCANNER.list"
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO-F401RE_I2C_ADDR_SCANNER.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "NUCLEO-F401RE_I2C_ADDR_SCANNER.hex"
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO-F401RE_I2C_ADDR_SCANNER.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "NUCLEO-F401RE_I2C_ADDR_SCANNER.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) NUCLEO-F401RE_I2C_ADDR_SCANNER.bin NUCLEO-F401RE_I2C_ADDR_SCANNER.elf NUCLEO-F401RE_I2C_ADDR_SCANNER.hex NUCLEO-F401RE_I2C_ADDR_SCANNER.list NUCLEO-F401RE_I2C_ADDR_SCANNER.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
