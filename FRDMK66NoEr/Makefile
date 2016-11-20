
PROJECT_NAME               := ArtTouch
PROJECT_BOARD              := FRDM-K66F
PROJECT_DEVICE             := MK66F18
PROJECT_MCU                := MK66FN2M0VMD18

COMMA                       = ,

CMSIS_BASE                 := CMSIS_5/CMSIS
CMSIS_DSP_BASE             := $(CMSIS_BASE)/DSP

TEMPLATE_SED_JLINK_FLASH   := flash.jlink

CALL_RMDIR                  = rm -rf $(1)
CALL_MOVE                   = mv -f $(1) $(2)
CALL_FIND_ALL_C_FILES       = $(foreach srcdir, $(1), $(wildcard $(srcdir)/*.c))
CALL_JLINK_FLASH            = JLinkExe -device $(1) -if SWD -speed 4000 -autoconnect 1 -CommanderScript $(2)

MACRO_PYTHON                = python
MACRO_MKDIRS               := mkdir -p
MACRO_ENSURE_TARGET_DIRS    = @[ -d "$(dir $@)" ] || $(MACRO_MKDIRS) "$(dir $@)"
MACRO_SED                  := sed

DIR_ROOT                   := $(abspath .)
DIR_BUILD                  := build/debug/$(PROJECT_BOARD)
DIR_KSDK                   := SDK_2.1_$(PROJECT_BOARD)-GCC-Full

TOOLCHAIN_PREFIX           := arm-none-eabi-
TOOLCHAIN_OBJCPY           := $(TOOLCHAIN_PREFIX)objcopy
TOOLCHAIN_OBJDUMP          := $(TOOLCHAIN_PREFIX)objdump
TOOLCHAIN_SIZE             := $(TOOLCHAIN_PREFIX)size
TOOLCHAIN_CC               := $(TOOLCHAIN_PREFIX)gcc

PROJECT_ASFLAGS            := -mfloat-abi=hard \
                              -mfpu=fpv4-sp-d16 \
                              -mcpu=cortex-m4 \
                              -mthumb \

PROJECT_LIBS               := m \
                              arm_cortexM4lf_math \

PROJECT_LDFLAGS            := --specs=nano.specs \
                              --specs=nosys.specs \
                              -Wl,--gc-sections \
                              -Wl,-L$(DIR_ROOT)/$(CMSIS_BASE)/Lib/GCC \

PROJECT_CFLAGS             := -O0 \
                              -DCPU_$(PROJECT_MCU) \
                              -D__FPU_PRESENT=1 \
                              -DPRINTF_ADVANCED_ENABLE \
                              -DPRINTF_FLOAT_ENABLE \
                              -DARM_MATH_CM4 \
                              -DDEBUG \
                              -fdata-sections \
                              -ffunction-sections \
                              -fsigned-char \
                              -flto \
                              -mlong-calls \
                              -g3 \
                              -Werror \
                              -Wall \
                              -Wno-unused \
                              -Wextra \
                              -pipe \
                              -fno-strict-aliasing \
                              -std=c11 \

PROJECT_HEX                := $(DIR_BUILD)/$(PROJECT_NAME).hex
PROJECT_ELF                := $(DIR_BUILD)/$(PROJECT_NAME).elf
PROJECT_LSS                := $(DIR_BUILD)/$(PROJECT_NAME).lss
PROJECT_INCLUDE_PATHS      := include \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE) \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/utilities \
                              $(CMSIS_DSP_BASE)/Include \
                              $(CMSIS_BASE)/Core/Include \

PROJECT_ARCHIVES           :=
PROJECT_LD_SCRIPT          := $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/gcc/MK66FN2M0xxx18_flash.ld
PROJECT_ASSEMBLY           := $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/gcc/startup_MK66F18.S
PROJECT_SOURCE             := source/board.c \
                              source/clock_config.c \
                              source/pin_mux.c \
                              source/touchy.c \
                              $(call CALL_FIND_ALL_C_FILES, $(DIR_KSDK)/devices/$(PROJECT_DEVICE)) \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers/fsl_clock.c \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/utilities/fsl_debug_console.c \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers/fsl_uart.c \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers/fsl_lpuart.c \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers/fsl_lptmr.c \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers/fsl_adc16.c \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers/fsl_pmc.c \
                              $(DIR_KSDK)/devices/$(PROJECT_DEVICE)/drivers/fsl_smc.c \
 
PROJECT_OBJECTS            := $(addprefix $(DIR_BUILD)/,$(PROJECT_ASSEMBLY:.S=.o) $(PROJECT_SOURCE:.c=.o))

.PHONY : all clean info disassemble size flash console

all : $(PROJECT_HEX) ;

clean : ;
	$(call CALL_RMDIR,$(DIR_BUILD))

info : 
	@echo PROJECT_OBJECTS = $(addprefix "\n\t",$(PROJECT_OBJECTS))
	@echo PROJECT_ASSEMBLY = $(addprefix "\n\t",$(PROJECT_ASSEMBLY))
	@echo PROJECT_SOURCE = $(addprefix "\n\t",$(PROJECT_SOURCE))

size : $(PROJECT_ELF)
	$(TOOLCHAIN_SIZE) $<

disassemble : $(PROJECT_LSS)
	@less $<

flash : $(DIR_BUILD)/$(TEMPLATE_SED_JLINK_FLASH)
	$(call CALL_JLINK_FLASH, $(PROJECT_MCU), $<)

console :
	$(MACRO_PYTHON) -m serial.tools.miniterm /dev/tty.usbmodem1411 115200

$(DIR_BUILD)/$(TEMPLATE_SED_JLINK_FLASH) : $(TEMPLATE_SED_JLINK_FLASH) $(PROJECT_HEX)
	$(MACRO_SED) 's/\%BINARY/$(subst /,\/,$(filter %.hex,$^))/' <$< > $@

$(PROJECT_LSS) : $(PROJECT_ELF)
	$(MACRO_ENSURE_TARGET_DIRS)
	$(TOOLCHAIN_OBJDUMP) -h -S $< > $@

$(PROJECT_HEX) : $(PROJECT_ELF)
	$(MACRO_ENSURE_TARGET_DIRS)
	$(TOOLCHAIN_OBJCPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

$(PROJECT_ELF) : $(PROJECT_OBJECTS) $(PROJECT_ARCHIVES) $(PROJECT_LD_SCRIPT)
	$(MACRO_ENSURE_TARGET_DIRS)
	$(TOOLCHAIN_CC) $(PROJECT_ASFLAGS) \
                    $(PROJECT_CFLAGS) \
                    $(PROJECT_LDFLAGS) \
                    -Wl,-Map="$(basename $@).map"\
                    -Wl,--cref \
                    $(addprefix -T,$(filter-out %.a %.o, $^)) \
                    $(filter %.o %.a, $^) -o $@ \
                    $(addprefix -Wl$(COMMA)-l,$(PROJECT_LIBS))

$(addprefix $(DIR_BUILD)/,$(PROJECT_SOURCE:.c=.o)) : $(DIR_BUILD)/%.o : %.c $(DIR_BUILD)/%.d
	$(MACRO_ENSURE_TARGET_DIRS)
	$(TOOLCHAIN_CC) -c \
                    $(PROJECT_ASFLAGS) \
                    -MT $@ -MMD -MP -MF "$(patsubst %.o,%.Td,$@)" \
                    $(PROJECT_CFLAGS) \
                    $(addprefix -I,$(PROJECT_INCLUDE_PATHS)) \
                    $< \
                    -o $@
	$(call CALL_MOVE, $(patsubst %.o,%.Td,$@), $(patsubst %.o,%.d,$@))

$(addprefix $(DIR_BUILD)/,$(PROJECT_ASSEMBLY:.S=.o)) : $(DIR_BUILD)/%.o : %.S $(DIR_BUILD)/%.d
	$(MACRO_ENSURE_TARGET_DIRS)
	$(TOOLCHAIN_CC) -c \
                    $(PROJECT_ASFLAGS) \
                    -MT $@ -MMD -MP -MF "$(patsubst %.o,%.Td,$@)" \
                    $(PROJECT_CFLAGS) \
                    $(addprefix -I,$(PROJECT_INCLUDE_PATHS)) \
                    $< \
                    -o $@
	$(call CALL_MOVE, $(patsubst %.o,%.Td,$@), $(patsubst %.o,%.d,$@))

%d : ;

.PRECIOUS: %.d

-include $(PROJECT_OBJECTS:.o=.d)
