# File: Makefile
# Author: dgrubb
# Date: 12/12/2017
#
# Usage:
#
# make          # Build the project
# make clean    # Delete compiled objects
# make upload   # Use OpenOCD to program the target device
# make debug    # Open a debugging session with the target
# make run_gdb  # Connect to a debugging session

# Session options
TARGET = Jaguar-USB-tap
DEBUG = 1
OPT = -Og
BUILD_DIR = build

################################################################################
# Tool aliases
################################################################################

# Build tools
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
GDB = $(PREFIX)gdb
# Programming tools
OPENOCD = openocd
# Filetype flags
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

################################################################################
# Source paths
################################################################################

SOURCES_DIR  = Middlewares
SOURCES_DIR += Drivers/STM32F0xx_HAL_Driver
SOURCES_DIR += Drivers/CMSIS
SOURCES_DIR += Application
SOURCES_DIR += Application/User/Src
SOURCES_DIR += Drivers
SOURCES_DIR += Middlewares/USB_Device_Library
SOURCES_DIR += Application/User

################################################################################
# Source files
################################################################################

# HAL Cube drivers
C_SOURCES  = Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim_ex.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd_ex.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash_ex.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pcd.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_i2c_ex.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr_ex.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_tim.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_pwr.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_dma.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_flash.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc_ex.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c
C_SOURCES += Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.c
# STM Middleware
C_SOURCES += Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c
C_SOURCES += Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
C_SOURCES += Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
C_SOURCES += Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
# Project source
C_SOURCES += Src/usb_device.c
C_SOURCES += Src/stm32f0xx_it.c
C_SOURCES += Src/stm32f0xx_hal_msp.c
C_SOURCES += Src/usb_device.c
C_SOURCES += Src/stm32f0xx_it.c
C_SOURCES += Src/usbd_desc.c
C_SOURCES += Src/usbd_conf.c
C_SOURCES += Src/usbd_desc.c
C_SOURCES += Src/stm32f0xx_hal_msp.c
C_SOURCES += Src/system_stm32f0xx.c
C_SOURCES += Src/usbd_conf.c
C_SOURCES += Src/main.c

# ASM sources
ASM_SOURCES = startup_stm32f070xb.s

# Linker script
LDSCRIPT = STM32F070CBTx_FLASH.ld

################################################################################
# Include directories
################################################################################

C_INCLUDES  = -I./Inc
C_INCLUDES += -I./Drivers/STM32F0xx_HAL_Driver/Inc
C_INCLUDES += -I./Drivers/STM32F0xx_HAL_Driver/Inc/Legacy
C_INCLUDES += -I./Middlewares/ST/STM32_USB_Device_Library/Core/Inc
C_INCLUDES += -I./Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc
C_INCLUDES += -I./Drivers/CMSIS/Device/ST/STM32F0xx/Include
C_INCLUDES += -I./Drivers/CMSIS/Include

################################################################################
# Compilation flags
################################################################################

CPU = -mcpu=cortex-m0
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
C_DEFS = -DUSE_HAL_DRIVER -DSTM32F070xB

ASFLAGS = $(MCU) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

LIBS = -lc -lm -lnosys
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections,--allow-multiple-definition

###############################################################################
# Upload commands
###############################################################################

OPENOCD_CFG = /usr/share/openocd/scripts/interface/stlink-v2-1.cfg
OPENOCD_TARGET_CFG = /usr/share/openocd/scripts/target/stm32f0x.cfg
OPENOCD_ARGS  = -f $(OPENOCD_CFG)
OPENOCD_ARGS += -f $(OPENOCD_TARGET_CFG)
# Upload
OPENOCD_UPLOAD_CMDS  = -c init
OPENOCD_UPLOAD_CMDS += -c 'reset halt'
OPENOCD_UPLOAD_CMDS += -c 'sleep 10'
OPENOCD_UPLOAD_CMDS += -c 'flash write_image erase $(BUILD_DIR)/$(TARGET).hex'
OPENOCD_UPLOAD_CMDS += -c 'sleep 10'
OPENOCD_UPLOAD_CMDS += -c 'reset run'
OPENOCD_UPLOAD_CMDS += -c shutdown
# OpenOCD start debugging interface
OPENOCD_DEBUG_CMDS = -c init
OPENOCD_DEBUG_CMDS += -c 'halt'
OPENOCD_DEBUG_CMDS += -c 'sleep 10'
# GDB debugging commands
GDB_CMDS = -ex "target remote localhost:3333"
GDB_CMDS += -ex "file $(BUILD_DIR)/$(TARGET).elf"
GDB_CMDS += -ex "mon reset halt"
GDB_CMDS += -ex "tbreak main"
# Uncomment to allow application to run before user can attach to a GDB session
#GDB_CMDS += -ex "c"

###############################################################################
# Compilation targets
###############################################################################

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR .dep $(BUILD_DIR)

# Upload program to target device
# N.B: Make sure you have permissions to access the STLink USB device
upload:
	$(OPENOCD) $(OPENOCD_ARGS) $(OPENOCD_UPLOAD_CMDS)

debug:
	$(OPENOCD) $(OPENOCD_ARGS) $(OPENOCD_DEBUG_CMDS)

run_gdb:
	$(GDB) $(GDB_ARGS) $(GDB_CMDS)

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

