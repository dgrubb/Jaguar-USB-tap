# File: Makefile
# Author: dgrubb
# Date: 11/21/2017
# 
# Usage:
#
# make          # Build the project
# make clean    # Delete compiled objects
# make upload   # Use OpenOCD to program the target device
# make debug    # Open a debugging session with the target
# make run_gdb  # Connect to a debugging session

###############################################################################
# Tool aliases
###############################################################################

# Compiler utilities
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
GDB = arm-none-eabi-gdb

# OpenOCD related
OPENOCD = openocd

###############################################################################
# Compilation flags
###############################################################################

OCFLAGS = --strip-unneeded
CFLAGS = -I./CMSIS/Include/
CFLAGS += -I./STM32F0xx_HAL_Driver/Inc/
CFLAGS += -I./CMSIS/Device/ST/STM32F0xx/Include/
CFLAGS += -I./ -c -fno-common -Os -g -mcpu=cortex-m4 -mthumb -Wall -ffunction-sections -fdata-sections -fno-builtin -Wno-unused-function -ffreestanding
LFLAGS = -Tstm32f0.ld -nostartfiles -Wl,--gc-sections

# Specify the uC being targeted, necessary for the HAL libraries
CFLAGS += -DSTM32F070x6

###############################################################################
# Upload commands
###############################################################################

# This is somewhat particular to STM32F0 chips on the Nucleo board with
# integrated STLink. Edit as appropriate.
OPENOCD_CFG = /usr/local/share/openocd/scripts/interface/stlink-v2-1.cfg
OPENOCD_TARGET_CFG = /usr/local/share/openocd/scripts/target/stm32f0x.cfg
OPENOCD_ARGS = -f $(OPENOCD_CFG)
OPENOCD_ARGS += -f $(OPENOCD_TARGET_CFG)
OBJCOPY_ARGS = -Oihex
# Upload
OPENOCD_UPLOAD_CMDS = -c init
OPENOCD_UPLOAD_CMDS += -c 'reset halt'
OPENOCD_UPLOAD_CMDS += -c 'sleep 10'
OPENOCD_UPLOAD_CMDS += -c 'flash write_image erase main.hex'
OPENOCD_UPLOAD_CMDS += -c 'sleep 10'
OPENOCD_UPLOAD_CMDS += -c 'reset run'
OPENOCD_UPLOAD_CMDS += -c shutdown
# Debug
OPENOCD_DEBUG_CMDS = -c init
OPENOCD_DEBUG_CMDS += -c 'halt'
OPENOCD_DEBUG_CMDS += -c 'sleep 10'
GDB_CMDS = -ex "target remote localhost:3333"
GDB_CMDS += -ex "file main.elf"
GDB_CMDS += -ex "mon reset halt"
GDB_CMDS += -ex "tbreak main"
# Uncomment to allow application to run before user can attach to a GDB session
#GDB_CMDS += -ex "c"

###############################################################################
# Project code
###############################################################################

OBJS =  main.o
OBJS += gpio/gpio.o
OBJS += jaguar/jaguar-controller.o
# STM32 platform related
OBJS += handlers.o startup.o

###############################################################################
# ST and ARM libraries
###############################################################################

OBJS += STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_rcc.o
OBJS += STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_gpio.o
OBJS += STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.o
OBJS += STM32F0xx_HAL_Driver/Src/stm32f0xx_hal.o
OBJS += STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_cortex.o
OBJS += CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.o

###############################################################################
# Compilation targets
###############################################################################

# Build and clean application objects

all: main.bin

clean:
	-rm -f $(OBJS) main.lst main.elf main.hex main.map main.bin main.list

main.elf: $(OBJS) stm32f0.ld
	$(LD) $(LFLAGS) -o main.elf $(OBJS)
	-@echo ""
	$(SIZE) main.elf
	-@echo ""

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.bin: %.elf
	$(OBJCOPY) $(OCFLAGS) -O binary $< $@

# Upload program to target device
# N.B: Make sure you have permissions to access the STLink USB device
upload:
	$(OBJCOPY) $(OBJCOPY_ARGS) main.elf main.hex && \
	$(OPENOCD) $(OPENOCD_ARGS) $(OPENOCD_UPLOAD_CMDS)

debug:
	$(OPENOCD) $(OPENOCD_ARGS) $(OPENOCD_DEBUG_CMDS)

run_gdb:
	$(GDB) $(GDB_ARGS) $(GDB_CMDS)
