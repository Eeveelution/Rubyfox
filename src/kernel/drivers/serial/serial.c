#include "serial.h"
#include "../../arch/port.h"

int serial_port_create(uint16_t port, serial_port* out) {
    out->port = port;

    outb(port + 1, 0x00); // Disable interrupts
    outb(port + 3, 0x80); // Set Baud Rate Divisor
    outb(port + 1, 0x03); // Set divisor to 3 (low byte); 38400 Baud
    outb(port + 1, 0x00); // high byte
    outb(port + 3, 0x03); // 8bit, no parity, 1 stop bit
    outb(port + 2, 0xC7); // FIFO, 14 byte threshold
    outb(port + 4, 0x0B); // irq enabled
    outb(port + 4, 0x1E); // loopback mode
    outb(port + 0, 0xAE); // test bytes

    uint8_t input = inb(port);

    if(input != 0xAE) {
        return -1;
    }

    //enable operation
    outb(port + 4, 0x0F);

    return 0;
}

int serial_write_clear(serial_port* serial) {
    return inb(serial->port + 5) & 0x20;
}

void serial_port_write(serial_port* serial, uint8_t data) {
    while(serial_write_clear(serial) == 0);

    outb(serial->port, data);    
}

int serial_data_available(serial_port* serial) {
    return inb(serial->port + 5) & 1;
}

void serial_port_read_byte(serial_port* serial, uint8_t* out) {
    while(serial_data_available(serial) == 0);

    *out = inb(serial->port);
}

void serial_port_write_string(serial_port* serial, const char* data) {
    int i = 0;

    while(data[i] != 0) {
        serial_port_write(serial, data[i]);
        i++;
    }
}