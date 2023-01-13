import subprocess

CC = "i686-elf-gcc"
AS = "i686-elf-as"
CFLAGS = "-std=gnu99 -ffreestanding -O2 -Wall -Wextra"
LDFLAGS = "-ffreestanding -O2 -nostdlib -lgcc"

cFindOutput = subprocess.check_output(['find', './', "-name", "*.c"])
cFindSplit = cFindOutput.split(b'\n')

asFindOutput = subprocess.check_output(['find', './', "-name", "*.asm"])
asFindSplit = asFindOutput.split(b'\n')

print("#!/bin/bash")
print("set -e")

objects = []

for byteStr in cFindSplit:
    str = byteStr.decode("utf-8")

    if str == "":
        continue

    str = str.lstrip("./")
    str = str.lstrip("/")

    objectName = "build/" + str.replace("/", "__") + ".o"

    objects.append(objectName)

    print(CC, CFLAGS, "-c", str, "-o " + objectName)

for byteStr in asFindSplit:
    str = byteStr.decode("utf-8")

    if str == "":
        continue

    str = str.lstrip("./")
    str = str.lstrip("/")

    objectName = "build/" + str.replace("/", "__") + ".o"

    objects.append(objectName)

    print(AS, str, "-o " + objectName)

print(CC, "-T linker.ld -o rubyfox.bin", LDFLAGS, " ".join(objects))

print("mkdir -p isoroot/boot/grub")
print("cp rubyfox.bin isoroot/boot/rubyfox.bin")
print("cp grub.cfg isoroot/boot/grub/grub.cfg")
print("grub-mkrescue -o rubyfox.iso isoroot")
