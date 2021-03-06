AS=nasm
ASFLAGS=-f elf32
CC=gcc
CFLAGS=-ffreestanding -fno-stack-protector -fno-pie -m32 -O0 -c
LDFLAGS=-melf_i386
KERNOBJ=src/boot/bootloader.o src/kernel/kernel.o src/display/console.o src/architecture/gdt.o src/architecture/idt.o src/architecture/interrupts.o src/architecture/pic.o src/architecture/trampoline.o src/architecture/ports.o src/features/keyboard.o

all: Pluto.iso

Pluto.iso: Pluto.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "Pluto" {' >> iso/boot/grub/grub.cfg
	echo 'multiboot /boot/Pluto.bin' >> iso/boot/grub/grub.cfg
	echo 'boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso

Pluto.bin: linker.ld $(KERNOBJ)
	ld $(LDFLAGS) -T $< -o $@ $(KERNOBJ)

src/boot/bootloader.o: src/boot/bootloader.asm
	$(AS) $(ASFLAGS) src/boot/bootloader.asm -o src/boot/bootloader.o

src/kernel/kernel.bin: $(KERNOBJ)
	ld -o src/kernel/kernel.bin -Ttext 0x7e00 $(KERNOBJ) -m elf_i386 --oformat binary

src/kernel/%.o: src/kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

src/display/%.o: src/display/%.c
	$(CC) $(CFLAGS) $< -o $@

src/architecture/trampoline.o: src/architecture/trampoline.asm
	$(AS) $(ASFLAGS) src/architecture/trampoline.asm -o src/architecture/trampoline.o

src/architecture/%.o: src/architecture/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	find . -name *.o -exec rm -rf '{}' \;
	find . -name *.bin -exec rm -rf '{}' \;
	rm -rf iso
	rm *.iso