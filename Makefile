#---------------#
#---Toolchain---#
#---------------#
CC 		:= $(TARGET)-gcc
AS 		:= $(CC)
LD		:= $(TARGET)-ld

#PATHS
#Architecture specific
ARCH_DIR		:= kernel/arch/aarch64
#Kernel
KERNELSRC_DIR 	:= kernel/src
KERNELINC_DIR 	:= kernel/include
#Libc/k
LIBCSTR_DIR		:= libc/string
LIBCINC_DIR		:= libc/include
#Libfdt
LIBFDTSRC_DIR	:= libfdt/src
LIBFDTINC_DIR	:= libfdt/include
#Build
BUILD_DIR 		:= build
BIN_DIR			:= bin


#CFLAGS
CFLAGS 	:= -I$(KERNELINC_DIR) -I$(LIBCINC_DIR) -I$(LIBFDTINC_DIR) -mcpu=cortex-a53 -fpic -ffreestanding


#SOURCE
SRC_C       := bsp_virt.c mmio.c pl011.c kernel.c dtb.c
SRC_S       := boot.S
SRC_LIBC	:= memchr.c memcpy.c memset.c strcmp.c strncmp.c strrchr.c memcmp.c memmove.c strchr.c strlen.c strnlen.c

LIBFDT_C   	:= fdt.c fdt_ro.c fdt_strerror.c fdt_addresses.c fdt_check.c fdt_rw.c fdt_wip.c


#OBJECTS
COBJS       := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_C))
LIBC_OBJS   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_LIBC))
SOBJS       := $(patsubst %.S,$(BUILD_DIR)/%.o,$(SRC_S))
LIBFDT_OBJS := $(patsubst %.c,$(BUILD_DIR)/libfdt_%.o,$(LIBFDT_C))
OBJS        := $(SOBJS) $(COBJS) $(LIBC_OBJS) $(LIBFDT_OBJS)
DEPS        := $(OBJS:.o=.d)


#TARGETS
.PHONY: all clean dirs
all: dirs $(BIN_DIR)/kernel.elf

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

#RULES
# Assemble .S (preprocessed assembly)
$(BUILD_DIR)/%.o: $(ARCH_DIR)/%.S | $(BUILD_DIR)
	$(AS) $(CFLAGS) -c -o $@ $<

# Compile C from src/
$(BUILD_DIR)/%.o: $(KERNELSRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

#libc
$(BUILD_DIR)/%.o: $(LIBCSTR_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C from libfdt/src/, keep object names distinct with 'libfdt_' prefix
$(BUILD_DIR)/libfdt_%.o: $(LIBFDTSRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Link the kernel
$(BIN_DIR)/kernel.elf: $(OBJS) $(ARCH_DIR)/linker.ld | $(BIN_DIR)
	$(LD) -T $(ARCH_DIR)/linker.ld -o $@ $(OBJS)

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
