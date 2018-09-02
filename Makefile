AS=nasm
ASFLAGS=-f elf32
CC=gcc
CFLAGS=-ffreestanding -fno-stack-protector -fno-pie -m32 -O0 -c
LDFLAGS=-melf_i386
KERNOBJ=src/boot/bootloader.o src/kernel/kernel.o

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

src/kernel/%.0: src/kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	find . -name *.o -exec rm -rf '{}' \;
	find . -name *.bin -exec rm -rf '{}' \;
	rm -rf iso
	rm *.iso