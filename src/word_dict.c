/**
* Authors : Florian BROSSARD - florian.brossard@edu.univ-fcomte.fr
*			Victor NAGY 	 - victor.nagy@edu.univ-fcomte.fr
*
* Description : Word dictionary functions
*
**/

#include "word_dict.h"

#define CAPACITY 16
// Determines the processor's architecture
#if(UINTPTR_MAX == 0xffffffffffffffff)
	//x64 OS
	#define	FNV_PRIME 1099511628211
	#define OFFSET_BASIS 14695981039346656037
#else
	//x86 OS
	#define	FNV_PRIME 16777619
	#define OFFSET_BASIS 2166136261
#endif

/**
*
* Adds an element to a linked list possibly empty and returns the new linked list.
*
**/
struct word_dict_bucket *word_dict_bucket_add(struct word_dict_bucket *self, const char *word){
	struct word_dict_bucket *new = malloc(sizeof(struct word_dict_bucket));
	new->word = word;
	new->next = self;
	return new;
}
/**
*
* Destroys a linked list possibly empty.
*
**/
void word_dict_bucket_destroy(struct word_dict_bucket *self){
	if(self == NULL) return;
	struct word_dict_bucket *tmp;
	while(self != NULL){
		tmp = self;
		self = self->next;
		free(tmp);
	}
}
/**
*
* Creates an empty dictionary.
*
**/
void word_dict_create(struct word_dict *self){
	self->size = CAPACITY;
	self->count = 0;
	self->buckets = calloc(self->size, sizeof(struct word_dict_bucket));
}
/**
*
* Destroys a dictionary, destroys all linked lists but not the words.
*
**/
void word_dict_destroy(struct word_dict *self){
	if(self != NULL && self->size < 1) return;
	for(size_t i=0; i<self->size; i++){
		word_dict_bucket_destroy(self->buckets[i]);
	}
	self->count = 0;
	free(self->buckets);
	self->buckets = NULL;
}

/* http://www.isthe.com/chongo/tech/comp/fnv/index.html
hash = offset_basis
for each octet_of_data to be hashed
		hash = hash xor octet_of_data
		hash = hash * FNV_prime
return hash
*/
/**
*
* Calculates a FNV hash, copy the key and then sort the letters before 
* calculating the hash.
*
**/
size_t fnv_hash(const char *key){
	char *save = string_duplicate(key);
	string_sort_letters(save);

	size_t hash = OFFSET_BASIS;
	size_t i=0;
	while(save[i] != '\0'){
		hash ^= save[i++];
		hash *= FNV_PRIME;
	}
	free(save);
	return hash;
}
/**
*
* Does a rehash.
*
**/
void word_dict_rehash(struct word_dict *self){
	self->size *= 2;
	struct word_dict_bucket **newBuckets = calloc(self->size,sizeof(struct word_dict_bucket*));
	size_t i = 0;
	size_t newIdx;
	size_t count = 0;
	struct word_dict_bucket *curr;
	struct word_dict_bucket *next;
	while(count < self->count){
		curr = self->buckets[i];
		while(curr != NULL){
			next = curr->next;
			newIdx = fnv_hash(curr->word) % self->size;
			newBuckets[newIdx] = word_dict_bucket_add(newBuckets[newIdx],curr->word);
			count++;
			free(curr);
			curr = next;
		}
		i++;
	}
	free(self->buckets);
	self->buckets = newBuckets;
}
/**
*
* Adds an entry in the dictionary.
* A rehash is done if necessary.
*
**/
void word_dict_add(struct word_dict *self, const char *word){
	double fact = (double)(self->count) / (double)(self->size);
	if(fact >= 0.5){
		word_dict_rehash(self);
	}
	size_t index = fnv_hash(word) % self->size;
	self->buckets[index] = word_dict_bucket_add(self->buckets[index],word);
	self->count++;
}
/**
*
* Fills a dictionary with words contained in a word_array.
*
**/
void word_dict_fill_with_array(struct word_dict *self, const struct word_array *array){
	for(size_t i=0; i<array->size; i++){
		word_dict_add(self,array->data[i]);
	}
}
/**
*
* Searches for anagrams of a word in a dictionary.
* Anagrams found will be placed in a word_array.
*
**/
void word_dict_search_anagrams(const struct word_dict *self, const char *word, struct word_array *result){
	if(word == NULL)
	{
		return ;
	}
	size_t idx = fnv_hash(word) % self->size;
	struct word_dict_bucket *curr = self->buckets[idx];
	while(curr != NULL){
		if(string_are_anagrams(word,curr->word)){
			word_array_add(result,curr->word);
		}
		curr = curr->next;
	}
}
/**
*
* Prints a dictionary of words.
*
**/
void word_dict_print(const struct word_dict *self){
	size_t i = 0;
	size_t count = 0;
	struct word_dict_bucket *curr;
	while(count < self->count){
		if(self->buckets[i] != NULL){
			curr = self->buckets[i];
			while(curr != NULL){
				printf("%s",curr->word);
				curr = curr->next;
				count++;
			}
			word_dict_bucket_destroy(self->buckets[i]);
		}
		i++;
	}
}