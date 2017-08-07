/**
* Authors : Florian BROSSARD - florian.brossard@edu.univ-fcomte.fr
*			Victor NAGY 	 - victor.nagy@edu.univ-fcomte.fr
*
* Description : Wildcard operations functions
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wildcard.h"
#include "word_array.h"

/**
*
* Initializes a wildcard
*
**/
void wildcard_create(struct wildcard *self) {
	self->count = 0;
	for(int i = 0; i < WILDCARDS_MAX; i++) {
		self->index[i] = 0;
	}
}
/**
*
* Searches index of wildcard(s) in a string (word).
*
**/
void wildcard_search(struct wildcard *self, const char *word) {
	size_t length = strlen(word);
	size_t i = 0;
	const char c = '*';
	while(i < length && self->count <= WILDCARDS_MAX) {
		if(c == (word[i])) {
			self->index[self->count] = i;
			self->count++;
		}
		i++;
	}
}


/**
*
* Searches anagrams in a word array with a word including wildcards.
*
*/
//On place les valeurs entières de chaques lettre du mot source dans un tableau d'entier,
//on compare avec le tableau du mot courant et si le nombre de différences (en termes d'occurences de lettres) entre eux
//est égal au nombre de joker, ce sont des anagrammes
void word_array_search_anagrams_wildcard(const struct word_array *self, const char *word, struct word_array *result) {
	struct wildcard joker;
	wildcard_create(&joker);
	wildcard_search(&joker,word);
	if(joker.count > WILDCARDS_MAX){
		fprintf(stderr, "Error : too much wildcards\n");
		exit(EXIT_FAILURE);
	}
	size_t t1[26];
	size_t t2[26];
	size_t i;
	size_t diffCount = 0;//compteur de différences
	size_t j;
	size_t sz = strlen(word);
	size_t sz2;

	for(i=0; i<26; i++){//initialisation des tableaux
		t1[i] = 0;
		t2[i] = 0;
	}

	for(i=0; i<sz; i++){//comptage du nombre de lettres dans word
		if(word[i] != '*' && word[i] != '\0'){
			t1[word[i]-'a']++;
		}
	}

	for(i=0; i<self->size; i++){//pour chaque mots de self
		sz2 = strlen(self->data[i]);
		if(sz == sz2){
			for(j=0; j<sz2; j++){
				if( self->data[i][j] != '\0'){
					t2[ self->data[i][j] - 'a' ]++;
				}
			}

			for(j=0; j<26; j++){//comparaison des occurences et réinitialisation du tableau
				if(t2[j] != t1[j]){
					diffCount += abs(t2[j] - t1[j]);
				}
				t2[j] = 0;
			}
			if(diffCount == joker.count){//anagrammes ?
				word_array_add(result,self->data[i]);
			}
			diffCount = 0;
		}
	}

}
/**
*
* Searches anagrams in a dictionnary with a word including wildcards.
*
*/
void word_dict_search_anagrams_wildcard(const struct word_dict *self, const char *word, struct word_array *result){
	struct wildcard joker;
	wildcard_create(&joker);
	wildcard_search(&joker,word);
	if(joker.count > WILDCARDS_MAX){
		fprintf(stderr, "Error : too much wildcards\n");
		exit(EXIT_FAILURE);
	}
	else{
		word_dict_search_anag_wc_rec(self,word,result,0);
	}
}
/**
*
* Recursive method used in word_dict_search_anagrams_wildcard to find anagrams in a dictionnary with a word including wildcards.
*
*/
void word_dict_search_anag_wc_rec(const struct word_dict *self, const char *word, struct word_array *result, size_t n){
	struct wildcard joker;
	wildcard_create(&joker);
	wildcard_search(&joker,word);
	if(joker.count == 0){
		word_dict_search_anagrams(self,word,result);
	}
	else{
		char *dup;
		for(size_t i=n; i<26; i++){
				dup = string_duplicate(word);
				dup[joker.index[0]] = 'a'+i;
				word_dict_search_anag_wc_rec(self,dup,result,i);
				free(dup);
		}
	}
}