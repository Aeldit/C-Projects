#include "tinyprintf.h"

/**************************************
**              MISC
**************************************/
int str_len(const char *s)
{
    if (s == NULL)
    {
        return 0;
    }

    int ctr = 0;
    while (s[ctr] != '\0')
    {
        ctr++;
    }
    return ctr;
}

/**
** \brief Returns an int corresponding to the type of the directive
**
** \param directive: the directive whose type we want
**                   (Can be: d | u | s | c | o | x)
**
** \returns An int from the AVAILABLE_TYPES enum.
**          If no correct directive is found, NONE (= -1) is returned
*/
int get_type(char directive)
{
    switch (directive)
    {
    case 'd':
        return INT;
    case 'u':
        return UINT;
    case 's':
        return CHAR_ARRAY;
    case 'c':
        return CHAR;
    case 'o':
        return UOCT;
    case 'x':
        return UHEX;
    default:
        break;
    }
    return NONE;
}

int nb_digits(int n)
{
    int nb_digits = 0;
    int tmp = n;
    while (tmp >= 10)
    {
        tmp /= 10;
        nb_digits++;
    }
    return nb_digits;
}

int nb_udigits(unsigned n)
{
    int nb_digits = 0;
    unsigned tmp = n;
    while (tmp >= 10)
    {
        tmp /= 10;
        nb_digits++;
    }
    return nb_digits;
}

/**************************************
**              PRINTS
**************************************/
int print_number(int arg, int nb_digits)
{
    if (nb_digits == 0)
    {
        putchar(arg + '0');
        return 1;
    }
    char c = arg % 10 + '0';
    int nb_printed = 1 + print_number(arg / 10, nb_digits - 1);
    putchar(c);
    return nb_printed;
}

int print_unumber(unsigned arg, int nb_digits)
{
    if (nb_digits == 0)
    {
        putchar(arg + '0');
        return 1;
    }
    char c = arg % 10 + '0';
    int nb_printed = 1 + print_unumber(arg / 10, nb_digits - 1);
    putchar(c);
    return nb_printed;
}

int print_octal(int n)
{
    if (n < 8)
    {
        putchar(n + '0');
        return 1;
    }
    int tmp = n % 8;
    int nb_printed = 1 + print_octal(n / 8);
    putchar(tmp + '0');
    return nb_printed;
}

int print_hex(long n)
{
    if (n < 16)
    {
        putchar(n < 10 ? n + '0' : n % 10 + 'a');
        return 1;
    }
    int tmp = n % 16;
    int nb_printed = 1 + print_hex(n / 16);
    putchar(tmp < 10 ? tmp + '0' : tmp % 10 + 'a');
    return nb_printed;
}

int print_char_array(const char *arg)
{
    int len = str_len(arg);
    for (int i = 0; i < len; i++)
    {
        putchar(arg[i]);
    }
    return len;
}

int print_null(void)
{
    putchar('(');
    putchar('n');
    putchar('u');
    putchar('l');
    putchar('l');
    putchar(')');
    return 6;
}

/*******************************************************************************
** MAIN FUNCTIONS
*******************************************************************************/
int handle_directive(int directive, va_list ap)
{
    if (directive == NONE)
    {
        return 0;
    }
    if (directive == INT)
    {
        int arg = va_arg(ap, int);
        int nb_printed = 0;
        if (arg < 0)
        {
            putchar('-');
            nb_printed++;
            arg *= -1;
        }
        return nb_printed + print_number(arg, nb_digits(arg));
    }
    if (directive == UINT)
    {
        unsigned uarg = va_arg(ap, unsigned);
        return print_unumber(uarg, nb_udigits(uarg));
    }
    if (directive == CHAR_ARRAY)
    {
        char *arr = va_arg(ap, char *);
        return arr == NULL ? print_null() : print_char_array(arr);
    }
    if (directive == CHAR)
    {
        putchar(va_arg(ap, int));
        return 1;
    }
    if (directive == UOCT)
    {
        return print_octal(va_arg(ap, int));
    }
    if (directive == UHEX)
    {
        return print_hex(va_arg(ap, long));
    }
    return 0;
}

int tinyprintf(const char *format, ...)
{
    va_list ap;
    int nb_printed = 0;

    va_start(ap, format);
    char prev = '\0';
    // If the current % is a directive and not an argument
    int dir_percent = 0;

    for (int i = 0; i < str_len(format); i++)
    {
        dir_percent = !dir_percent && prev == '%';
        // Aquires the directive
        // if the previous character was not the '%' directive
        int directive = prev == '%' && dir_percent ? get_type(format[i]) : NONE;

        if (directive == NONE && format[i] != '%')
        {
            if (prev == '%')
            {
                putchar('%');
                nb_printed++;
            }
            putchar(format[i]);
            nb_printed++;
        }

        prev = format[i];

        // Takes action depending on the directive
        nb_printed += handle_directive(directive, ap);
    }
    va_end(ap);

    return nb_printed;
}
