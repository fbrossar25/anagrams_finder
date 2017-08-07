#ifndef WORD_ARRAY_H
#define WORD_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "string_op.h"

struct word_array{
	char **data;
	size_t size;
	size_t capacity;
};

void word_array_create(struct word_array *self);

void word_array_destroy(struct word_array *self);

void word_array_add(struct word_array *self, const char *word);

void word_array_search_anagram(const struct word_array *self, const char *word, struct word_array *result);

void word_array_sort(struct word_array *self);

void word_array_print(const struct word_array *self);

void word_array_read_file(struct word_array *self, const char *filename);


#endif