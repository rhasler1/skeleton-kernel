#---------------#
#---Toolchain---#
#---------------#

INCLUDE_DIR := include

CC 		:= $(TARGET)-gcc
AS 		:= $(CC)
LD		:= $(TARGET)-ld
CFLAGS 	:= -I$(INCLUDE_DIR) -mcpu=cortex-a53 -fpic -ffreestanding

#---------------#
#---PATHS-------#
#---------------#
SRC_DIR 	:= src
#INCLUDE_DIR := include
BUILD_DIR 	:= build
BIN_DIR		:= bin

#---------------#
#---FILES-------#
#---------------#
#OBJS = boot.o kernel.o

#---------------#
#---RULES-------#
#---------------#
$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot.S
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/bsp_virt.o: $(SRC_DIR)/bsp_virt.c $(INCLUDE_DIR)/bsp_virt.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/mmio.o: $(SRC_DIR)/mmio.c $(INCLUDE_DIR)/mmio.h 
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/pl011.o: $(SRC_DIR)/pl011.c $(INCLUDE_DIR)/pl011.h $(INCLUDE_DIR)/bsp_virt.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c $(INCLUDE_DIR)/pl011.h $(INCLUDE_DIR)/bsp_virt.h
	$(CC) $(CFLAGS) -c -o $@ $< 

$(BIN_DIR)/kernel.elf: $(BUILD_DIR)/boot.o $(BUILD_DIR)/bsp_virt.o $(BUILD_DIR)/mmio.o $(BUILD_DIR)/pl011.o $(BUILD_DIR)/kernel.o $(SRC_DIR)/linker.ld
	$(LD) -T $(SRC_DIR)/linker.ld -o $@ $(BUILD_DIR)/boot.o $(BUILD_DIR)/bsp_virt.o $(BUILD_DIR)/mmio.o $(BUILD_DIR)/pl011.o $(BUILD_DIR)/kernel.o

#---------------#
#---TARGETS-----#
#---------------#
all: $(BIN_DIR)/kernel.elf

clean:
	rm -f $(OBJS) kernel.elf

run: $(BIN_DIR)/kernel.elf
	$(BUILD_SYSTEM)/$(BUILD_TARGET) -machine virt -nographic -cpu cortex-a53 -m 256M -kernel $(BIN_DIR)/kernel.elf
