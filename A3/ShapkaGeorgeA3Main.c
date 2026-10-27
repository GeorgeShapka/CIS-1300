#include "ShapkaGeorgeA3.h"

#define PUNCTUATION 12

void normalize(char line[]);
int tokenize(const char line[], char tokens[][MAX_WORD]);

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
         if(line[index] == punctuation[i]){
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
   while(line[lineIndex] != '\0'){
      if(line[lineIndex] != ' '){
         tokens[wordIndex][letterIndex] = line[lineIndex];
         ++letterIndex;
      }
      if(line[lineIndex] == ' '){
         ++wordIndex;
         letterIndex = 0;
      }
      ++lineIndex;
   }
}