#ifndef VGA_H
#define VGA_H

#include "int.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

uint8_t port_byte_in(uint16_t port);

void port_byte_out(uint16_t port, uint8_t data);

void put_pixel(uint32_t pos_x, uint32_t pos_y, uint8_t VGA_COLOR);

void clear_pixel(uint32_t pos_x, uint32_t pos_y);

#endif /* VGA_H */
