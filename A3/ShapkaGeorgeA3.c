#include "ShapkaGeorgeA3.h"

// REMEMBER to change this file name to the required format of lastnameFirstnameA3.c

// function definition of readInput

int readInput(FILE * inputData,
                char stop[][MAX_WORD],
                int * numStop,
                char variant[][MAX_WORD],
                char lemma[][MAX_WORD],
                int * numLemma,
                char post[][MAX_LEN]) {

   
   int i;
   int num;
   char line [MAX_LEN];
   
   // read num of stop words
   
   fscanf(inputData, "%d", &num);
   fgetc(inputData);
   
   *numStop = num;
   
   // read the stop words
   
   for (i = 0; i < num; i++) {
      fgets (line, MAX_LEN, inputData);
      line [strlen (line) - 1] = '\0';
      strcpy( stop[i],line);
   }
   
   // repeat the same as above for lemma pairs
   
   fscanf(inputData, "%d", &num);
   fgetc(inputData);
   
   *numLemma = num;
   
   for (i = 0; i < num; i++) {
      fgets (line, MAX_LEN, inputData);        // read the variant
      line [strlen (line) - 1] = '\0';
      strcpy( variant[i],line);
      
      fgets (line, MAX_LEN, inputData);        // read the lemma
      line [strlen (line) - 1] = '\0';
      strcpy( lemma[i],line);
   }
   
   // repeat the same as above for posts
   
   fscanf(inputData, "%d", &num);
   fgetc(inputData);
   
   for (i = 0; i < num; i++) {
      fgets (line, MAX_LEN, inputData);
      line [strlen (line) - 1] = '\0';
      strcpy( post[i],line);
   }
   
   return num;          // return num of posts read
}

// define all other functions here
