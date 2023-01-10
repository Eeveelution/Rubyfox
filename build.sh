#!/bin/bash
set -e
i686-elf-gcc -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c src/arch/port.c -o build/src__arch__port.c.o
i686-elf-gcc -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c src/drivers/serial/serial.c -o build/src__drivers__serial__serial.c.o
i686-elf-gcc -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c src/kernel_main.c -o build/src__kernel_main.c.o
i686-elf-as src/boot.asm -o build/src__boot.asm.o
i686-elf-gcc -T linker.ld -o rubyfox.bin -ffreestanding -O2 -nostdlib -lgcc build/src__arch__port.c.o build/src__drivers__serial__serial.c.o build/src__kernel_main.c.o build/src__boot.asm.o
mkdir -p isoroot/boot/grub
cp rubyfox.bin isoroot/boot/rubyfox.bin
cp grub.cfg isoroot/boot/grub/grub.cfg
grub-mkrescue -o rubyfox.iso isoroot
