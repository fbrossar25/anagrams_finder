/**
* Authors : Florian BROSSARD - florian.brossard@edu.univ-fcomte.fr
*			Victor NAGY 	 - victor.nagy@edu.univ-fcomte.fr
*
* Description : Application which finds anagrams from sequence of words or letters
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "string_op.h"
#include "word_array.h"
#include "word_dict.h"
#include "wildcard.h"

#define BUFSIZE 32

/**
*
* Replaces the final line feed character by \0 in a buffer
*
**/
void clean_newline(char *buf, size_t size) {
	for(size_t i=0; i<size; i++){
		if(buf[i] == '\n'){
			buf[i] = '\0';
			return;
		}
	}
}
/**
*
* Main function
*
* In the input loop, asks a word (or a sequence of letters) and prints
* all anagrams in alphabetical order. It cares about wildcards. 
* It will show in the end, the number of anagrams found
* and the time taken to find them in microseconds.
* It realizes this twice, once with the word array and another with the
* dictionary in order to check that both return the same
* results.
*
* Using a FNV hash algorithm helps to speed the processing of data.
**/
int main(int argc, char *argv[]){
	char buf[BUFSIZE];
	struct timeval begin;
	struct timeval end;
	struct word_array anagArray;
	struct word_array anagDict;
	struct word_array array;
	word_array_create(&array);
	word_array_read_file(&array,"resources/dictionnaire.txt");
	//word_array_sort(&array);

	struct word_dict dict;
	word_dict_create(&dict);
	word_dict_fill_with_array(&dict,&array);

	printf("Readed %zu words in array, %zu in dict\n",array.size,dict.count);
	printf("%d wildcard max.\n",WILDCARDS_MAX);
	printf("Please, enter a word or sequence of letters :\n");
	// input loop, if the entered string is empty, break the loop
	for (;;) {
		printf("> ");
		if(fgets(buf, BUFSIZE, stdin) == NULL){
			fprintf(stderr,"Error : Can't read standard input\n");
			break;
		}
		clean_newline(buf, BUFSIZE);

		if(strcmp(buf,"") == 0) {
			printf("Exiting...\n\n");
			break;
		}

		
		if(gettimeofday(&begin, NULL) == -1){
			fprintf(stderr, "Error : Can't get time of day.\n");
		}

		printf("\n\n===============WITH ARRAY==============\n");

		word_array_create(&anagArray);
		word_array_search_anagrams_wildcard(&array, buf, &anagArray);
		word_array_sort(&anagArray);
		word_array_print(&anagArray);
		printf("%zu anagrams found\n",anagArray.size);
		word_array_destroy(&anagArray);

		if(gettimeofday(&end, NULL) == -1){
			fprintf(stderr, "Error : Can't get time of day.\n");
		}

		printf("Execution time for word_array : %zu µs\n",((end.tv_sec - begin.tv_sec) * 1000000) + (end.tv_usec - begin.tv_usec));

		if(gettimeofday(&begin, NULL) == -1){
			fprintf(stderr, "Error : Can't get time of day.\n");
		}

		printf("\n\n===============WITH DICT===============\n");

		word_array_create(&anagDict);
		word_dict_search_anagrams_wildcard(&dict, buf, &anagDict);
		word_array_sort(&anagDict);
		word_array_print(&anagDict);
		printf("%zu anagrams found\n",anagDict.size); 
		word_array_destroy(&anagDict);

		if(gettimeofday(&end, NULL) == -1){
			fprintf(stderr, "Error : Can't get time of day.\n");
		}

		printf("Execution time for word_dict : %zu µs\n",((end.tv_sec - begin.tv_sec) * 1000000) + (end.tv_usec - begin.tv_usec));
	}
	word_array_destroy(&array);
	word_dict_destroy(&dict);

	return EXIT_SUCCESS;
}
