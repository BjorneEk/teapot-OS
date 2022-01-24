#ifndef PORTS_H
#define PORTS_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "../../utils/include/int.h"



uint8_t in_portb(uint16_t port);

void out_portb(uint16_t port, uint8_t data);

#endif /* PORTS_H */
