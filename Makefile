all:
	python3 build.py > build.sh
	chmod +x build.sh
	mkdir -p build
	./build.sh

iso:
	mkdir -p isoroot/boot/grub
	cp rubyfox.bin isoroot/boot/rubyfox.bin
	cp grub.cfg isoroot/boot/grub/grub.cfg
	grub-mkrescue -o rubyfox.iso isoroot

run:
	qemu-system-i386 -kernel rubyfox.bin -serial stdio