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


BUILD_ARTIFACT_NAME := CODE_HE_THONG_KHOA_CUA
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CODE_HE_THONG_KHOA_CUA.elf \

MAP_FILES += \
CODE_HE_THONG_KHOA_CUA.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CODE_HE_THONG_KHOA_CUA.list \

OBJCOPY_HEX += \
CODE_HE_THONG_KHOA_CUA.hex \

OBJCOPY_BIN += \
CODE_HE_THONG_KHOA_CUA.bin \


# All Target
all: main-build

# Main-build Target
main-build: CODE_HE_THONG_KHOA_CUA.elf secondary-outputs

# Tool invocations
CODE_HE_THONG_KHOA_CUA.elf CODE_HE_THONG_KHOA_CUA.map: $(OBJS) $(USER_OBJS) D:\Dai_Hoc\Ki_2_Nam_3\THUC_TAP_CO_SO\BAI_TAP_CUOI_KY\SOURCE_CODE\CODE_HE_THONG_KHOA_CUA\STM32F401RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "CODE_HE_THONG_KHOA_CUA.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\Dai_Hoc\Ki_2_Nam_3\THUC_TAP_CO_SO\BAI_TAP_CUOI_KY\SOURCE_CODE\CODE_HE_THONG_KHOA_CUA\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CODE_HE_THONG_KHOA_CUA.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CODE_HE_THONG_KHOA_CUA.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CODE_HE_THONG_KHOA_CUA.list"
	@echo 'Finished building: $@'
	@echo ' '

CODE_HE_THONG_KHOA_CUA.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "CODE_HE_THONG_KHOA_CUA.hex"
	@echo 'Finished building: $@'
	@echo ' '

CODE_HE_THONG_KHOA_CUA.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "CODE_HE_THONG_KHOA_CUA.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) CODE_HE_THONG_KHOA_CUA.bin CODE_HE_THONG_KHOA_CUA.elf CODE_HE_THONG_KHOA_CUA.hex CODE_HE_THONG_KHOA_CUA.list CODE_HE_THONG_KHOA_CUA.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
