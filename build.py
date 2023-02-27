import subprocess

CC = "i686-elf-gcc"
AS = "i686-elf-as"
CFLAGS = "-std=gnu99 -ffreestanding -g -Wall -Wextra -I./src"
OBJCFLAGS = "-std=gnu99 -ffreestanding -nostdlib -lgcc -r -g -I./src"
LDFLAGS = "-ffreestanding -nostdlib -lgcc -g"

cFindOutput = subprocess.check_output(['find', './', "-name", "*.c"])
cFindSplit = cFindOutput.split(b'\n')

asFindOutput = subprocess.check_output(['find', './', "-name", "*.asm"])
asFindSplit = asFindOutput.split(b'\n')

objcFindOutput = subprocess.check_output(['find', './', "-name", "*.m"])
objcFindSplit = objcFindOutput.split(b'\n')

print("#!/bin/bash")
print("set -e")

objects = []

def processFilename(filename: bytearray):
    str = filename.decode("utf-8")

    if str == "":
        return "", ""

    str = str.lstrip("./")
    str = str.lstrip("/")

    objectName = "build/" + str.replace("/", "__") + ".o"

    objects.append(objectName)

    return str, objectName


for byteStr in cFindSplit:
    (str, objectName) = processFilename(byteStr)

    if str == "":
        continue

    print(CC, CFLAGS, "-c", str, "-o " + objectName)

for byteStr in asFindSplit:
    (str, objectName) = processFilename(byteStr)

    if str == "":
        continue

    if objectName == "":
        continue

    print(AS, str, "-o " + objectName)

#for byteStr in objcFindSplit:
#    (str, objectName) = processFilename(byteStr)
#
#    if str == "":
#        continue
#
#    print(CC, OBJCFLAGS, str, "-o " + objectName)

print("i686-elf-gcc -std=gnu99 -ffreestanding -nostdlib -lgcc -r -g -I./src src/kernel/kernel_main.m -o build/objc_core.o")

objects.append("build/objc_core.o")


print(CC, "-T linker.ld -o rubyfox.bin", LDFLAGS, " ".join(objects))