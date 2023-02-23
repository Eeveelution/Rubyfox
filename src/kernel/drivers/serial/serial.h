#ifndef __DRIVER_SERIAL_H_
#define __DRIVER_SERIAL_H_

#include <stddef.h>
#include <stdint.h>

#include "../../arch/port.h"

#define SERIAL_COM1 0x3F8
#define SERIAL_COM2 0x2F8
#define SERIAL_COM3 0x3E8
#define SERIAL_COM4 0x2F8
#define SERIAL_COM5 0x5F8
#define SERIAL_COM6 0x4F8
#define SERIAL_COM7 0x5E8
#define SERIAL_COM8 0x4E8

typedef struct {
    uint16_t port;
} serial_port;

/// @brief Creates a Serial Port and initializes it
/// @param port Serial port to bind to, SERIAL_COM1 for example
/// @param out Serial port return
/// @return 0 if success, -1 if error
int serial_port_create(uint16_t port, serial_port* out);
/// @brief Checks if the Serial Port is clear for writing
/// @param serial Serial Port
/// @return 0 if not clear, otherwise clear
int serial_write_clear(serial_port* serial);
/// @brief Checks serial port for available data
/// @param serial Serial Port
/// @return 0 if none, otherwise data available
int serial_data_available(serial_port* serial);
/// @brief Waits and Writes a single Byte to the Serial Port
/// @param serial Serial POrt
/// @param data Byte to write
void serial_port_write(serial_port* serial, uint8_t data);
/// @brief Waits and Reads a single byte from the serial port
/// @param serial Serial Port
/// @param out Output for read byte
void serial_port_read_byte(serial_port* serial, uint8_t* out);

void serial_port_write_string(serial_port* serial, const char* data);

#endif