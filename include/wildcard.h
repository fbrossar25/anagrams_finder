#ifndef WILDCARDS_H
#define WILDCARDS_H

#include <stdlib.h>
#include <stdio.h>
#include "word_dict.h"
#include "string_op.h"
#include "word_array.h"
#include "word_dict.h"

#define WILDCARDS_MAX 4

struct wildcard {
	size_t count;
	size_t index[WILDCARDS_MAX];
};

void wildcard_create(struct wildcard *self);

void wildcard_search(struct wildcard *self, const char *word);

void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result);

void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result);

void word_dict_search_anag_wc_rec(const struct word_dict *self, const char *word, struct word_array *result, size_t n);

#endif