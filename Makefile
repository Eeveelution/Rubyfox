all:
	python3 build.py > build.sh
	chmod +x build.sh
	./build.sh

run:
	qemu-system-i386 -kernel rubyfox.bin -serial stdio