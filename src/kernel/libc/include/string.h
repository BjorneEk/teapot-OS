#ifndef STRING_H
#define STRING_H

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

#include "int.h"

#define FLOAT_PRINT_ACCURACY 4

/**
 *   @breif calculates the length of a string;
 **/
uint32_t strlen(char * str);

/**
 *   @breif reverses a string;
 **/
void reverse(char s[]);

uint32_t nbr_of_digits(uint32_t n);

/**
 *   @breif converts a integer to a string;
 *
 *   turns a int32_t into a string, the lenght
 *   of the string will be the same as the amount of
 *   digits in the int + the \0 character;
 **/
int32_t itoa(int32_t x, char str[]);

/**
 *   @breif converts a float to a string;
 *
 *   turns a float into a string, the lenght
 *   of the string is the length of the integer
 *   part of the input plus a decimal point and
 *   'FLOAT_PRINT_ACCURACY' nbr of decimals
 **/
void ftoa(float n, char str[]);

/**
 *   @breif appends s2 to s1
 **/
char * strcat(char * s1, const char *s2);

#endif /* STRING_H */
