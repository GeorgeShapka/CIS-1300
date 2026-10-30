#include "ShapkaGeorgeA3.h"

#define PUNCTUATION 12
#define DEBUG

void normalize(char line[]);
int tokenize(const char line[], char tokens[][MAX_WORD]);
int removeStopWords(char tokens[][MAX_WORD], int numToken, char stop[][MAX_WORD], int numStop);
void applyLemmaMap(char tokens[][MAX_WORD], int count, char variant[][MAX_WORD], char lemma[][MAX_WORD], int L);
void shiftArrayLeft(char inputArray[][MAX_WORD], int maxStrings, int startIndex);

int main () {

   FILE * fileInput = NULL;
   
   char stop[MAX_STOP][MAX_WORD];
   char variant[MAX_LEMMA][MAX_WORD];
   char lemma[MAX_LEMMA][MAX_WORD];
   char post[MAX_POSTS][MAX_LEN];

   int numPosts;
   int numStops;
   int numLemma;
   
   char filename [20];
   
   printf ("Enter filename: ");
   scanf ("%s", filename);
   
   fileInput = fopen (filename, "r");
   numPosts = readInput (fileInput, stop, &numStops, variant, lemma, &numLemma, post);
   
   // call other functions here
   char tokens[MAX_TOKENS][MAX_WORD];
   for(int y = 0; y < MAX_TOKENS; y++){
      memset(tokens[y], '\0', MAX_WORD);
   }

   for(int i = 0; i < numPosts; i++){
      #ifdef DEBUG
         printf("String %s\n", post[i]);
      #endif

      normalize(post[i]);

      #ifdef DEBUG
         printf("\nNormalized %s\n", post[i]);
      #endif
      

      int t = tokenize(post[i], tokens);

      #ifdef DEBUG
         printf("\nTokens\n");

         for(int y = 0; y < t; y++){
            printf("%s\n", tokens[y]);
         }
      #endif

      int r = removeStopWords(tokens, t, stop, numStops);
      
      #ifdef DEBUG
         printf("\nRemoved Stop Words\n");
         for(int i = 0; i < r; i++){
            printf("%s\n", tokens[i]);
         }
         printf("----------------------------------\n\n");
      #endif
      
      for(int y = 0; y < MAX_TOKENS; y++){
         memset(tokens[y], '\0', MAX_WORD);
      }
   }
   
   
   fclose (fileInput);
   return 0;
}

void normalize(char line[]){
   int index = 0;
   char curr = line[index];
   char punctuation [PUNCTUATION] = {'.', ',', '!', '?', ':', ';', '\"', '(', ')', '[', ']', '\0'};
   while(curr != '\0'){
      if(line[index] <= 'Z' && line[index] >= 'A')
      {
         line[index] = line[index] + 32;//add 32 to map ascii caps to lowercase
      }
      for(int i = 0; i < PUNCTUATION; i++){
         if(line[index] == punctuation[i] && line[index] != '\0'){
            line[index] = 32;
         }
      }
      ++index;
      curr = line[index];
   }

   return;
}

int tokenize(const char line[], char tokens[][MAX_WORD]){
   int lineIndex = 0;
   int wordIndex = 0;
   int letterIndex = 0;
   int wordCount = 0;

   while(line[lineIndex] != '\0'){
      if(line[lineIndex] != ' '){
         tokens[wordIndex][letterIndex] = line[lineIndex];
         letterIndex++;
      }
      else if(line[lineIndex] == ' '){
         if(tokens[wordIndex][0] != ' ' && tokens[wordIndex][0] != '\0'){
            wordIndex++;
         }
         letterIndex = 0;
      }
      ++lineIndex;
   }
   for(int i = 0; i < MAX_TOKENS; i++){
      if(tokens[i][0] != '\0'){
         wordCount++;
      }
   }
   return(wordCount);
}

int removeStopWords(char tokens[][MAX_WORD], int numToken, char stop[][MAX_WORD], int numStop){
   bool match = false;
   int numTokenNew = numToken;
   for(int i = 0; i < numToken; i++){
      if(match){
         i--;
      }
      match = false;
      for(int y = 0; y < numStop; y++){
         if(strcmp(tokens[i], stop[y]) == 0){
            match = true;
            break;
         }
      }
      if(match){
         shiftArrayLeft(tokens, numToken, i);
         numTokenNew--;
      }
   }
   return numTokenNew;
}

void applyLemmaMap(char tokens[][MAX_WORD], int count, char variant[][MAX_WORD], char lemma[][MAX_WORD], int L){

}

void shiftArrayLeft(char inputArray[][MAX_WORD], int maxStrings, int startIndex){
    for (int i = startIndex; i < maxStrings - 1; i++) {
        strcpy(inputArray[i], inputArray[i + 1]);
    }

    inputArray[maxStrings - 1][0] = '\0';
}