#include "ShapkaGeorgeA3.h"

#define PUNCTUATION 12

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
   char tokens[MAX_TOKENS][MAX_WORD] = {0};

   for(int i = 0; i < numPosts; i++){
      printf("String %s\n", post[i]);
      normalize(post[i]);
      printf("\nNormalized %s\n", post[i]);

      int t = tokenize(post[i], tokens);
      printf("\nTokens\n");
      for(int i = 0; i < t; i++){
         printf("%s\n", tokens[i]);
      }

      int r = removeStopWords(tokens, t, stop, numStops);

      printf("\nRemoved Stop Words\n");
      for(int i = 0; i < r; i++){
         printf("%s\n", tokens[i]);
      }

      printf("----------------------------------\n\n");
      
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
         if(line[index] == punctuation[i] && line[index] != '\0"'){
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
   int tokenCount = 1;
   int letterIndex = 0;
   bool space = false;
   while(line[lineIndex] != '\0'){
      if(line[lineIndex] != ' '){
         tokens[wordIndex][letterIndex] = line[lineIndex];
         ++letterIndex;
         if(space == true){
            space = false;
            tokenCount++;
         }
      }
      else if(line[lineIndex] == ' '){
         ++wordIndex;
         letterIndex = 0;
         space = true;
      }
      ++lineIndex;
   }
   return(tokenCount);
}

int removeStopWords(char tokens[][MAX_WORD], int numToken, char stop[][MAX_WORD], int numStop){
   bool match = false;
   int numTokenNew = numToken;
   for(int i = 0; i < numToken; i++){
      for(int y = 0; y < numStop; y++){
         if(strcmp(tokens[i], stop[y])){// tokens[i][z] == stop[y][z] && tokens[i][z] != '\0'
            match = true;
            y = numStop;
            numTokenNew--;
         }
      }
      if(match == true){
         shiftArrayLeft(tokens, numToken, i);
      }
      match = false;
   }
   return numTokenNew;
}

void applyLemmaMap(char tokens[][MAX_WORD], int count, char variant[][MAX_WORD], char lemma[][MAX_WORD], int L){

}

void shiftArrayLeft(char inputArray[][MAX_WORD], int maxStrings, int startIndex){
   for(int i = startIndex; i < maxStrings; i++){
      if(inputArray[i + 1][0] == '\0'){
         inputArray[i][0] = '\0';
      }
      else{
         strcpy(inputArray[i], inputArray[i + 1]);
         printf("%s\n", inputArray[i]);
      }
   }
}