#---------------#
#---Toolchain---#
#---------------#
CC 		:= $(TARGET)-gcc
AS 		:= $(CC)
LD		:= $(TARGET)-ld

#---------------#
#---PATHS-------#
#---------------#
SRC_DIR 	:= src
INC_DIR 	:= include
LIBFDT_SRC	:= libfdt/src
LIBFDT_INC	:= libfdt/include
BUILD_DIR 	:= build
BIN_DIR		:= bin

#---------------#
#---CFLAGS------#
#---------------#
CFLAGS 	:= -I$(INC_DIR) -I$(LIBFDT_INC) -mcpu=cortex-a53 -fpic -ffreestanding

#---------------#
#---SOURCES-----#
#---------------#
# Your sources
SRC_C       := bsp_virt.c mmio.c pl011.c kernel.c dtb.c
SRC_S       := boot.S

LIBFDT_CS   := fdt.c fdt_ro.c fdt_strerror.c fdt_addresses.c fdt_check.c fdt_rw.c fdt_wip.c fdt_stubs.c

#---------------#
#---OBJECTS-----#
#---------------#
COBJS       := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_C))
SOBJS       := $(patsubst %.S,$(BUILD_DIR)/%.o,$(SRC_S))
LIBFDT_OBJS := $(patsubst %.c,$(BUILD_DIR)/libfdt_%.o,$(LIBFDT_CS))
OBJS        := $(SOBJS) $(COBJS) $(LIBFDT_OBJS)

DEPS        := $(OBJS:.o=.d)

#---------------#
#---TARGETS-----#
#---------------#
.PHONY: all clean dirs
all: dirs $(BIN_DIR)/kernel.elf

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

#---------------#
#---RULES-------#
#---------------#

# Assemble .S (preprocessed assembly)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(AS) $(CFLAGS) -c -o $@ $<

# Compile C from src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C from libfdt/src/, keep object names distinct with 'libfdt_' prefix
$(BUILD_DIR)/libfdt_%.o: $(LIBFDT_SRC)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Link the kernel
$(BIN_DIR)/kernel.elf: $(OBJS) $(SRC_DIR)/linker.ld | $(BIN_DIR)
	$(LD) -T $(SRC_DIR)/linker.ld -o $@ $(OBJS)

# Include auto-generated header deps (safe if missing the first time)
-include $(DEPS)

#---------------#
#---UTIL--------#
#---------------#
dump_dtb:
	$(BUILD_SYSTEM)/$(BUILD_TARGET) -machine virt,dumpdtb=virt.dtb -m 256M -nographic

run: $(BIN_DIR)/kernel.elf
	$(BUILD_SYSTEM)/$(BUILD_TARGET) -machine virt -nographic -cpu cortex-a53 -m 256M -kernel $(BIN_DIR)/kernel.elf

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
