#ifndef PORTS_H
#define PORTS_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../../libc/include/int.h"

/**
 *   functions used by drivers to read and write to
 *   port b
 */
uint8_t in_portb(uint16_t port);

void out_portb(uint16_t port, uint8_t data);

#endif /* PORTS_H */
