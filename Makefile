#toolchain
CC 		:= $(TARGET)-gcc
AS 		:= $(CC)
LD		:= $(TARGET)-ld


#directories
ARCH_DIR		:= kernel/arch/aarch64

KERNELSRC_DIR 	:= kernel/src
KERNELINC_DIR 	:= kernel/include

LIBCSTR_DIR		:= libc/string
LIBCINC_DIR		:= libc/include

LIBFDTSRC_DIR	:= libfdt/src
LIBFDTINC_DIR	:= libfdt/include

BUILD_DIR 		:= build
BIN_DIR			:= bin


#compiler flags
CFLAGS 	:= -I$(KERNELINC_DIR) \
		   -I$(LIBCINC_DIR) \
		   -I$(LIBFDTINC_DIR) \
		   -fpic \
		   -ffreestanding \
		   -Wall \
		   -O2


#source files
SRC_C       := mmio.c \
			   uart0.c \
			   kernel.c

SRC_S       := boot.S

SRC_LIBC	:= memchr.c \
			   memcpy.c \
			   memset.c \
			   strcmp.c \
			   strncmp.c \
			   strrchr.c \
			   memcmp.c \
			   memmove.c \
			   strchr.c \
			   strlen.c \
			   strnlen.c

LIBFDT_C   	:= fdt.c \
			   fdt_ro.c \
			   fdt_strerror.c \
			   fdt_addresses.c \
			   fdt_check.c \
			   fdt_rw.c \
			   fdt_wip.c


#object files to generate
COBJS       := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_C))
LIBC_OBJS   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_LIBC))
SOBJS       := $(patsubst %.S,$(BUILD_DIR)/%.o,$(SRC_S))
LIBFDT_OBJS := $(patsubst %.c,$(BUILD_DIR)/libfdt_%.o,$(LIBFDT_C))
OBJS        := $(SOBJS) $(COBJS) $(LIBC_OBJS) $(LIBFDT_OBJS)
DEPS        := $(OBJS:.o=.d)


#rules
#assemble .S (preprocessed assembly)
$(BUILD_DIR)/%.o: $(ARCH_DIR)/%.S | $(BUILD_DIR)
	$(AS) $(CFLAGS) -c -o $@ $<

#compile c from kernel/src
$(BUILD_DIR)/%.o: $(KERNELSRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

#compile c from libc/string
$(BUILD_DIR)/%.o: $(LIBCSTR_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

#compile C from libfdt/src/
$(BUILD_DIR)/libfdt_%.o: $(LIBFDTSRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

#link
$(BIN_DIR)/kernel8.elf: $(OBJS) $(ARCH_DIR)/linker.ld | $(BIN_DIR)
	$(LD) -T $(ARCH_DIR)/linker.ld -o $@ $(OBJS)

-include $(DEPS)


#targets
.PHONY: all dirs dunp_dtb machine_help run kernel8.img run_trace clean
all: dirs \
	$(BIN_DIR)/kernel8.elf \
	kernel8.img

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

dump_dtb:
	$(BUILD_SYSTEM)/$(BUILD_TARGET) \
		-dtb bcm2711-rpi-4-b.dtb \
		-machine raspi4b,dumpdtb=bcm2711-rpi-4-b.dtb \
		-nographic

machine_help:
	$(BUILD_SYSTEM)/$(BUILD_TARGET) \
		-machine help

run: $(BIN_DIR)/kernel8.elf
	$(BUILD_SYSTEM)/$(BUILD_TARGET) \
	-machine raspi4b \
	-nographic \
	-kernel $(BIN_DIR)/kernel8.img

kernel8.img:
	aarch64-elf-objcopy -O binary $(BIN_DIR)/kernel8.elf $(BIN_DIR)/kernel8.img

run_trace: $(BIN_DIR)/kernel8.elf
	$(BUILD_SYSTEM)/$(BUILD_TARGET) \ 
		-machine raspi4b \ 
		-nographic \
		-kerneil $(BIN_DIR)/kernel8.elf \
		-trace pl011*

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
