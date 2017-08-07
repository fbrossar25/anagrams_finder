#ifndef STRING_OP_H
#define STRING_OP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool string_are_anagrams(const char *str1, const char *str2);

char *string_duplicate(const char *str);

void string_sort_letters(char *str);

#endif