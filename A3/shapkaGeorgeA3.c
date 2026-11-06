//FILE: shapkaGeorgeA3.c
//DEVELOPER: George Shapka

#ifndef GIVEN_A3_H
#define GIVEN_A3_H
#include "givenA3.h"
#endif
// REMEMBER to change this file name to the required format of lastnameFirstnameA3.c


//I use bool
#include <stdbool.h>

//constant I used
#define PUNCTUATION 12

//extra function
void shiftArrayLeft(char inputArray[][MAX_WORD], int maxStrings, int startIndex);


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

/// @brief takes a string and removes punctuation and coverts to lowercase
/// @param line 
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


/// @brief Takes a string and converts it to tokens
/// @param line 
/// @param tokens 
/// @return number of tokens
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


/// @brief removes stop words
/// @param tokens 
/// @param numToken 
/// @param stop 
/// @param numStop 
/// @return number of tokens remainnig
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
         shiftArrayLeft(tokens, numTokenNew, i);
         numTokenNew--;
      }
   }//end of token iteration

   return numTokenNew;
}//end of removeStopWords


/// @brief performs lemmatization on an array of words
/// @param tokens 
/// @param count 
/// @param variant 
/// @param lemma 
/// @param L 
void applyLemmaMap(char tokens[][MAX_WORD], int count, char variant[][MAX_WORD], char lemma[][MAX_WORD], int L){
   for(int i = 0; i < count; i++){
      for(int y = 0; y < L; y++){
         if(strcmp(tokens[i], variant[y]) == 0){
            strcpy(tokens[i], lemma[y]);
         }
      }//end of variant iteration
   }//end of token iteration
}//end of applyLemmaMap

/// @brief shifts an array of strings left by one index
/// @param inputArray 
/// @param maxStrings 
/// @param startIndex 
void shiftArrayLeft(char inputArray[][MAX_WORD], int maxStrings, int startIndex){

    for (int i = startIndex; i < maxStrings - 1; i++) {
        strcpy(inputArray[i], inputArray[i + 1]);
    }

    inputArray[maxStrings - 1][0] = '\0';
}//end of shiftArrayLeft