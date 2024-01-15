#ifndef TINYPRINTF_H
#define TINYPRINTF_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum AVAILABLE_TYPES
{
    NONE = -1,
    INT,
    UINT,
    CHAR_ARRAY,
    CHAR,
    UOCT,
    UHEX,
};

/**
** \returns The number of digits in n
*/
int nb_digits(int n);
int nb_udigits(unsigned n);

/**
** \brief Prints the given number in its octal representation
*/
int print_octal(int n);

/**
** \brief Prints the given number in its hexadecimal representation
*/
int print_hex(long n);

/**
** \brief Prints the char array arg
*/
int print_char_array(const char *arg);

/**
** \brief Prints '(null)' on the output
*/
int print_null(void);

/**
** \brief Takes action depending on the directive
*/
int handle_directive(int directive, va_list ap);

/**
** \brief Main function, handles the inputs
*/
int tinyprintf(const char *format, ...);

#endif /* TINYPRINTF_H */
