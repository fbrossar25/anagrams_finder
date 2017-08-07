/**
* Authors : Florian BROSSARD - florian.brossard@edu.univ-fcomte.fr
*			Victor NAGY 	 - victor.nagy@edu.univ-fcomte.fr
*
* Description : Strings operations functions
*
**/

#include "string_op.h"

/**
*
* Checks if string str1 and str2 are anagrams, returns a boolean.
*
**/
bool string_are_anagrams(const char *str1, const char *str2){
	char *s1 = string_duplicate(str1);
	char *s2 = string_duplicate(str2);
	string_sort_letters(s1);
	string_sort_letters(s2);

	bool res = (strcmp(s1,s2) == 0);
	free(s1);
	free(s2);
	return res;
}
/**
*
* Returns a point to a new string which is a duplicate of the string str.
* Need to be freed with free(3).
*
**/
char *string_duplicate(const char *str){
	size_t sz = strlen(str) + 1;
	char *res = calloc(sz,sizeof(char));
	for(size_t i=0; i<sz; i++){
		res[i] = str[i];
	}
	return res;
}
/**
*
* Sorts the letters of a string str in alphabetical order (Using insertion sort).
*
**/
void string_sort_letters(char *str){
	
	size_t length = strlen(str);
	char res[length];

	for(size_t i=0; i<length; i++){
		res[i] = str[i];
	}
	char c;
	size_t j;

	// Insertion sort
	for(size_t i=1; i<length; i++){
		c = res[i];
		j = i;
		while (j > 0 && res[j - 1] > c) {
			res[j] = res[j - 1];
			j--;
		}
		res[j] = c;
	}

	for(size_t i=0; i<length; i++){
		str[i] = res[i];
	}
	
}