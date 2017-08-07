#ifndef WORD_DICT_H
#define WORD_DICT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "string_op.h"
#include "word_array.h"

struct word_dict_bucket{
	const char *word;
	struct word_dict_bucket *next;
};

struct word_dict{
	struct word_dict_bucket **buckets;
	size_t count;
	size_t size;
};

struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *self, const char *word);

void word_dict_bucket_destroy(struct word_dict_bucket *self);

void word_dict_create(struct word_dict *self);

void word_dict_destroy(struct word_dict *self);

size_t fnv_hash(const char *key);

void word_dict_rehash(struct word_dict *self);

void word_dict_add(struct word_dict *self, const char *word);

void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array);

void word_dict_print(const struct word_dict *self);

void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result);

#endif