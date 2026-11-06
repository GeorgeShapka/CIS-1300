//FILE: shapkaGeorgeA3Main.c
//DEVELOPER: George Shapka

#ifndef GIVEN_A3_H
#define GIVEN_A3_H
#include "givenA3.h"
#endif
//#define DEBUG


int main (void) {

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
