#ifndef RLE_H
#define RLE_H

#include <stdlib.h>

/**
** \returns The lenght of the char array s
*/
unsigned str_len(const char *s);

/**
** \brief Adds the 'number:letter' key-pair to the compressed string
** \param comp_str: The compressed string
** \param current: The current letter
** \param nb_identical: The number of iteration of the letter
** \param pos_in_comp_str: The current index in the comp_str string
*/
void add_to_comp_str(char *comp_str, char current, unsigned nb_identical,
                     unsigned *pos_in_comp_str);

/**
** \returns The number of different characters in the string s.
**          If a character is present in more than just the base,
**          the counter is incermented accordingly
*/
unsigned nb_diff_letters(const char *s, unsigned nb_chars, char current,
                         unsigned base_max);

/**
** \returns 1 if errors where found | 0 otherwise
*/
int errors_found(unsigned char base, const char *s);

/**
** \returns the string "" if the string s is empty | NULL otherwise
*/
char *handle_errors(unsigned char base, const char *s);

/**
** \brief If not 0 <= c <= 9 && c is not a letter,
**        (upper and lower case), this returns 0
** \returns The char in its unsigned representation
**          (works in bases < 10 and in hexadecimal)
*/
unsigned my_atoi(char c);

char *compress(const char *string, unsigned char base);
char *decompress(const char *string, unsigned char base);

#endif /* RLE_H */
