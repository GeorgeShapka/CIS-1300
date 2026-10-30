#include "ShapkaGeorgeA3.h"

#define PUNCTUATION 12
//#define DEBUG

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

   printf("\n\n");
   
   //iterate posts
   for(int i = 0; i < numPosts; i++){   

      //clear token array   
      for(int y = 0; y < MAX_TOKENS; y++){
         memset(tokens[y], '\0', MAX_WORD);
      }

      printf("Post %d original: %s\n", i + 1, post[i]);


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
      #endif


      applyLemmaMap(tokens, r, variant, lemma, numLemma);
      #ifdef DEBUG
         printf("\nlemmatized\n");
         for(int i = 0; i < r; i++){
            printf("%s\n", tokens[i]);
         }
         printf("----------------------------------\n\n");
      #endif
      

      printf("Number of tokens = %d\n", t);
      printf("Number of stop words removed = %d\n", t - r);
      printf("Post %d cleaned: ", i + 1);
      //print tokens as a line
      for(int y = 0; y < r; y++){
         printf("%s", tokens[y]);
         if(y != r - 1){
            printf(" ");
         }
      }

      printf("\n\n");
   }//end of post iteration
   
   
   fclose (fileInput);
   return 0;
}//end of main



void normalize(char line[]){
   int index = 0;
   char punctuation [PUNCTUATION] = {'.', ',', '!', '?', ':', ';', '\"', '(', ')', '[', ']', '\0'};

   while(line[index] != '\0'){
      //check if a letter is capitilized and convert
      if(line[index] <= 'Z' && line[index] >= 'A')
      {
         line[index] = line[index] + 32;//add 32 to map ascii caps to lowercase
      }

      //check for punctuation and set to space
      for(int i = 0; i < PUNCTUATION; i++){
         if(line[index] == punctuation[i] && line[index] != '\0'){
            line[index] = 32;
         }
      }//end of punctuation iteration

      ++index;
   }//end of while loop to iterate through line

   return;
}//end of normalize



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
         //make sure past token is a word to avoid gaps in token array
         if(tokens[wordIndex][0] != ' ' && tokens[wordIndex][0] != '\0'){
            wordIndex++;
         }
         letterIndex = 0;
      }
      ++lineIndex;
   }//end of wile loop to tokenize

   //count tokens
   for(int i = 0; i < MAX_TOKENS; i++){
      if(tokens[i][0] != '\0'){
         wordCount++;
      }
   }//end of token counter

   return(wordCount);
}//end of tokenize



int removeStopWords(char tokens[][MAX_WORD], int numToken, char stop[][MAX_WORD], int numStop){
   bool match = false;
   int numTokenNew = numToken;

   for(int i = 0; i < numToken; i++){
      //if a match, the array is shifted left, so subtract from i to account for that
      if(match){
         i--;
      }
      match = false;

      //compare tokens to stop words
      for(int y = 0; y < numStop; y++){
         if(strcmp(tokens[i], stop[y]) == 0){
            match = true;
            break;
         }
      }//end of stop iteration

      if(match){
         shiftArrayLeft(tokens, numToken, i);
         numTokenNew--;
      }
   }//end of token iteration

   return numTokenNew;
}//end of removeStopWords



void applyLemmaMap(char tokens[][MAX_WORD], int count, char variant[][MAX_WORD], char lemma[][MAX_WORD], int L){
   for(int i = 0; i < count; i++){
      for(int y = 0; y < L; y++){
         if(strcmp(tokens[i], variant[y]) == 0){
            strcpy(tokens[i], lemma[y]);
         }
      }//end of variant iteration
   }//end of token iteration
}//end of applyLemmaMap



void shiftArrayLeft(char inputArray[][MAX_WORD], int maxStrings, int startIndex){
    for (int i = startIndex; i < maxStrings - 1; i++) {
        strcpy(inputArray[i], inputArray[i + 1]);
    }

    inputArray[maxStrings - 1][0] = '\0';
}//end of shiftArrayLeft