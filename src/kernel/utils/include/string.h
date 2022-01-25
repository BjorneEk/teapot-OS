#ifndef STRING_H
#define STRING_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "int.h"
uint32_t strlen(char * str);

void reverse(char s[]);

int int_to_str(int x, char str[], int d);

void ftoa(float n, char* res, int32_t afterpoint);

#endif /* STRING_H */
