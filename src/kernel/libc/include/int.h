#ifndef INT_H
#define INT_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#define true  1
#define false 0

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned int       size_t;
typedef unsigned int       uintptr_t;


typedef signed char      int8_t;
typedef signed short     int16_t;
typedef signed int       int32_t;

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)


#ifdef SYS_64_BIT
typedef unsigned long long int64_t;
typedef signed long long int64_t;
#endif /* SYS_64_BIT */
#endif /* INT_H */
