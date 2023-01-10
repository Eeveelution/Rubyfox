#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str) {
    size_t length = 0;

    while(str[length]) {
        length++;
    }

    return length;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void kernel_main() {
    uint16_t* vga_buffer = (uint16_t*) 0xB8000;

	for(int y = 0; y < 25; y++) {
		for(int x = 0; x < 80; x++) {
			const int index = y * 80 + x;
			vga_buffer[index] = vga_entry(' ', 15);
		}
	}

    const char* message = "Hello, Rubyfox!\n";
    size_t message_length = strlen(message);

    for(size_t i = 0; i != message_length; i++) {
        vga_buffer[i] = vga_entry(message[i], 15);
    }
}