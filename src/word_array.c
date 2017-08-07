/**
* Authors : Florian BROSSARD - florian.brossard@edu.univ-fcomte.fr
*			Victor NAGY 	 - victor.nagy@edu.univ-fcomte.fr
*
* Description : Word array functions
*
**/

#include "word_array.h"
#include <stdbool.h>

#define CAPACITY 16
#define WORD_LETTERS_MAX 32

/**
*
* Initializes an array
*
**/
void word_array_create(struct word_array *self) {
	self->size = 0;
	self->capacity = CAPACITY;
	self->data = calloc(CAPACITY,sizeof(char*));
}
/**
*
* Destroys an array, free after calloc in word_array_create().
*
**/
void word_array_destroy(struct word_array *self) {
	if(self->data == NULL) return;
	for(size_t i=0; i<self->size; i++){
		free(self->data[i]);
	}
	free(self->data);
	self->data = NULL;
	self->size = 0;
}
/**
*
* Adds a word in a word array.
*
**/
void word_array_add(struct word_array *self, const char *word) {
	if(self->size == self->capacity) {
		self->capacity *= 2;
		char **data = calloc(self->capacity,sizeof(char*));
		memcpy(data, self->data,self->size * sizeof(char*));
		free(self->data);
		self->data = data;
	}
	self->data[self->size] = string_duplicate(word);
	self->size++;
}
/**
*
* Finds anagrams of a word in word_array.
* Anagrams found will be placed in an another word_array.
*
**/
void word_array_search_anagram(const struct word_array *self, const char *word, struct word_array *result) {
	for(size_t i = 0; i < self->size; i++) {
		if(string_are_anagrams(word, self->data[i])){
			word_array_add(result, self->data[i]);
		}
	}
}

/**
*
* Swap the value of index i and, used for the quick sort
*
**/
void array_swap(struct word_array *self, size_t i, size_t j) {
	char *tmp = self->data[i];
	self->data[i] = self->data[j];
	self->data[j] = tmp;
}

/**
*
* Do a partition of data in self, used for the quick sort
*
**/
ssize_t array_partition(struct word_array *self, ssize_t i, ssize_t j) {
	ssize_t pivot_index = i;
	char *pivot = self->data[pivot_index];
	array_swap(self, pivot_index, j);
	ssize_t l = i;
	for (size_t k = i; k < j; ++k) {
		if (strcmp(self->data[k], pivot)<0) {
			array_swap(self, k, l);
			l++;
		}
	}
	array_swap(self, l, j);
	return l;
}

/**
*
* Call array_partition() recursively, used for the quick sort
*
**/
void word_array_sort_partial(struct word_array *self, ssize_t i, ssize_t j) {
	if (i < j) {
		ssize_t p = array_partition(self, i, j);
		word_array_sort_partial(self, i, p - 1);
		word_array_sort_partial(self, p + 1, j);
	}
}

/**
*
* Sorts a word_array using quick sort
*
**/
void word_array_sort(struct word_array *self) {
	word_array_sort_partial(self, 0, (self->size)-1);
}
/**
*
* Prints the contents of a word_array.
*
**/
void word_array_print(const struct word_array *self) {
	for(size_t i = 0; i < self->size; i++) {
		printf("%s\n", self->data[i]);
	}
}
/**
*
* Reads a file of words (one per line) and stores them in a word_array.
*
**/
void word_array_read_file(struct word_array *self, const char *file) {
	FILE *fp = fopen(file,"r");
	if(fp == NULL) {
		fprintf(stderr, "Error : Unable to open file '%s'\n",file);
		return;
	}
	char word[WORD_LETTERS_MAX];
	size_t i;
	while(fgets(word, WORD_LETTERS_MAX, fp) != NULL) {
		i = 0;
		while(word[i] != '\0'){
			if(word[i] == '\n'){
				word[i] = '\0';
			}
			i++;
		}
		word_array_add(self,word);
	}
	fclose(fp);
}