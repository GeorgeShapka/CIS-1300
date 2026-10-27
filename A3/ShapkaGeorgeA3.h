#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_POSTS   30
#define MAX_LEN     200
#define MAX_TOKENS  40
#define MAX_WORD    25
#define MAX_STOP    25
#define MAX_LEMMA   25
#define MAX_VOCAB   200

int readInput(FILE *, char stop[][MAX_WORD], int * numStop, char variant[][MAX_WORD], char lemma[][MAX_WORD], int * numLemma, char post[][MAX_LEN]);
void normalize(char line[]);
int tokenize(const char line[], char tokens[][MAX_WORD]);
int removeStopWords(char tokens[][MAX_WORD], int count, char stop[][MAX_WORD], int S);
void applyLemmaMap(char tokens[][MAX_WORD], int count, char variant[][MAX_WORD], char lemma[][MAX_WORD], int L);
