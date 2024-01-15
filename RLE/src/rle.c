#include "rle.h"

#include <stdlib.h>

#include "stdio.h"

unsigned str_len(const char *s)
{
    unsigned i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

void add_to_comp_str(char *comp_str, char current, unsigned nb_identical,
                     unsigned *pos_in_comp_str)
{
    comp_str[*pos_in_comp_str] =
        nb_identical < 10 ? nb_identical + '0' : (nb_identical) % 10 + 'A';
    comp_str[*pos_in_comp_str + 1] = current;
    *pos_in_comp_str += 2;
}

unsigned nb_diff_letters(const char *s, unsigned nb_chars, char current,
                         unsigned base_max)
{
    unsigned nb_diff_chars = 1;
    unsigned base_ctr = 1;
    for (unsigned i = 1; i < nb_chars; i++)
    {
        if (s[i] == current && base_ctr == base_max)
        {
            base_ctr = 1;
            nb_diff_chars++;
        }
        else if (s[i] != current)
        {
            base_ctr = 1;
            nb_diff_chars++;
            current = s[i];
        }
        base_ctr++;
    }
    return nb_diff_chars;
}

int errors_found(unsigned char base, const char *s)
{
    if ((base != 8 && base != 10 && base != 16) || s == NULL)
    {
        return 1;
    }
    if (s[0] == '\0')
    {
        return 1;
    }
    return 0;
}

char *handle_errors(unsigned char base, const char *s)
{
    if ((base != 8 && base != 10 && base != 16) || s == NULL)
    {
        return NULL;
    }
    if (s[0] == '\0')
    {
        char *empty = calloc(1, sizeof(char));
        if (empty == NULL)
        {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }
    return NULL;
}

char *compress(const char *string, unsigned char base)
{
    // Handle errors
    if (errors_found(base, string) == 1)
    {
        return handle_errors(base, string);
    }

    unsigned nb_chars = str_len(string);

    // Obtains the number of chars in the string to know which size to
    // allocate to the compressed string
    char current = string[0];
    unsigned diff_char = nb_diff_letters(string, nb_chars, current, base - 1);

    // Each letter will have 1 number assigned to it + '\0'
    char *comp_str = calloc(1, diff_char * 2 * sizeof(char) + 1);
    if (comp_str == NULL)
    {
        return NULL;
    }

    unsigned pos_in_comp_str = 0;
    unsigned i = 0;
    while (i < nb_chars)
    {
        current = string[i++];
        unsigned nb_identical = 1;

        while (string[i] == current && i < nb_chars)
        {
            nb_identical++;
            i++;
        }

        // Counts the number of times the base is in the total number
        // of identical letters and adds the commpressed letter to the string
        // in consequence
        unsigned nb_base_breaks = 0;
        for (; nb_base_breaks < nb_identical / (base - 1); nb_base_breaks++)
        {
            add_to_comp_str(comp_str, current, base - 1, &pos_in_comp_str);
        }

        // If the number of identical letter was superior to the base - 1,
        // we remove the number of times it was in it from the number of
        // identical letters
        if (nb_base_breaks != 0)
        {
            nb_identical -= nb_base_breaks * (base - 1);
        }

        // Adds the rest in the comp_str string
        if (nb_identical != 0)
        {
            add_to_comp_str(comp_str, current, nb_identical, &pos_in_comp_str);
        }
    }

    // If there was only 1 occurence of the last character
    if (current != string[nb_chars - 1])
    {
        comp_str[pos_in_comp_str] = '1';
        comp_str[pos_in_comp_str + 1] = string[nb_chars - 1];
    }

    comp_str[diff_char * 2 * sizeof(char)] = '\0';
    return comp_str;
}

unsigned my_atoi(char c)
{
    if ('0' <= c && c <= '9')
    {
        return c - '0';
    }
    else if ('a' <= c && c <= 'f')
    {
        // 'a' = 97 in ascii and '0' = 30, so 97 - 30 = 67
        return 10 + (c - 67) % 10;
    }
    else if ('A' <= c && c <= 'F')
    {
        // 'A' = 65 in ascii and '0' = 30, so 65 - 30 = 35
        return 10 + (c - 35) % 10;
    }
    return 0;
}

char *decompress(const char *string, unsigned char base)
{
    // Handles errors
    if (errors_found(base, string))
    {
        return handle_errors(base, string);
    }

    // Test if the string has an odd number of characters,
    // and returns NULL if so
    unsigned nb_chars = str_len(string);
    if (nb_chars % 2 != 0)
    {
        return NULL;
    }

    // Acquires the total number of chars that will be in the decompressed
    // string
    unsigned total_size = 0;
    for (unsigned i = 0; i < nb_chars; i++)
    {
        if (i % 2 == 0)
        {
            unsigned current_nb = my_atoi(string[i]);
            if (0 == current_nb || current_nb >= base)
            {
                return NULL;
            }
            total_size += current_nb;
        }
    }

    // Total numbe of characters + '\0'
    char *decomp_str = calloc(1, total_size * sizeof(char) + 1);
    if (decomp_str == NULL)
    {
        return NULL;
    }

    // Adds the characters to the decompressed string
    unsigned pos_in_decomp_str = 0;
    unsigned current_nb = 0;
    for (unsigned i = 0; i < nb_chars; i++)
    {
        if (i % 2 == 0)
        {
            current_nb = string[i];
        }
        else
        {
            char current = string[i];
            for (unsigned a = 0; a < my_atoi(current_nb); a++)
            {
                decomp_str[pos_in_decomp_str++] = current;
            }
        }
    }
    decomp_str[total_size * sizeof(char)] = '\0';
    return decomp_str;
}
