CC := i686-elf-gcc
AS := i686-elf-as

CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra

BUILDDIR := build
SRCDIR := ./

SOURCES := $(shell find $(SOURCEDIR) -name "*.c")
ASMSOURCES := $(shell find $(SOURCEDIR) -name "*.asm")

sources:
	for file in $(SOURCES) ; do \
   		$(CC) $(CFLAGS) -c $$file -o $(BUILDDIR)/$$file.o; \
    done;

assembly: $(SRCDIR)/*.asm
	for file in $^ ; do \
   		$(CC) $(CFLAGS) -c $${file} -o $(BUILDDIR)/$${file}.o; \
    done;

kernel: sources | assembly