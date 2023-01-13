all:
	python3 build.py > build.sh
	chmod +x build.sh
	mkdir -p build
	./build.sh

run:
	qemu-system-i386 -kernel rubyfox.bin -serial stdio