#---------------#
#---Toolchain---#
#---------------#
CC 		:= $(TARGET)-gcc
AS 		:= $(CC)
LD		:= $(TARGET)-ld
CFLAGS 	:= -mcpu=cortex-a53 -fpic -ffreestanding

#---------------#
#---PATHS-------#
#---------------#
SRC_DIR 	:= src
INC_DIR 	:= include
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

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c
	$(CC) $(CFLAGS) -c -o $@ $< 

$(BIN_DIR)/kernel.elf: $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(SRC_DIR)/linker.ld
	$(LD) -T $(SRC_DIR)/linker.ld -o $@ $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o

#---------------#
#---TARGETS-----#
#---------------#
all: $(BIN_DIR)/kernel.elf

clean:
	rm -f $(OBJS) kernel.elf

run: $(BIN_DIR)/kernel.elf
	$(BUILD_SYSTEM)/$(BUILD_TARGET) -machine virt -nographic -cpu cortex-a53 -m 256M -kernel $(BIN_DIR)/kernel.elf
