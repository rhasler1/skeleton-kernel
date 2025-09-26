CROSS	= aarch64-linux-gnu-
CC		= $(CROSS)gcc
LD		= $(CROSS)ld
CFLAGS	= -ffreestanding -nostdlib

OBJS = boot.o kernel.o uart.o mmio.o

all: kernel.elf

boot.o: boot.s
	$(CC) $(CFLAGS) -c -o $@ $<

kernel.o: kernel.c uart.h mmio.h
	$(CC) $(CFLAGS) -c -o $@ $<

uart.o: uart.c uart.h mmio.h
	$(CC) $(CFLAGS) -c -o $@ $<

mmio.o: mmio.c mmio.h
	$(CC) $(CFLAGS) -c -o $@ $<

kernel.elf: $(OBJS) linker.ld
	$(LD) -T linker.ld -o $@ $(OBJS)

run: kernel.elf
	/home/ryan/repos/qemu/qemu-10.1.0/build/qemu-system-aarch64 -machine virt -cpu cortex-a53 -m 256M -kernel kernel.elf -nographic

run_debug: kernel.elf
	/home/ryan/repos/qemu/qemu-10.1.0/build/qemu-system-aarch64 -machine virt -cpu cortex-a53 -m 256M -kernel kernel.elf -nographic -d guest_errors,unimp
clean:
	rm -f $(OBJS) kernel.elf
