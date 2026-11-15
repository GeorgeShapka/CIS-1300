#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define DAYS 7
#define MAX_NAME 50

typedef struct {
   
   /* these are read from the file*/
   int id;
   char name[MAX_NAME];
   
   int examWeek;     // 1 = yes, 0 = no
   double study [DAYS];
   double breaks [DAYS];
   double sleep [DAYS];
   
   //these are computed  for each student
   
   double studyContribution;
   double breakContribution;
   double sleepContribution;
   double overallScore;
   char grade;
   int atRisk;       // 1 = yes, 0 = no
   
} Student;

int readFile (FILE *, Student studentData [MAX_STUDENTS]);
void computeStudent (Student * studentData);
void printClassSummary(Student  [MAX_STUDENTS]);
void printAtRiskStudents(Student [MAX_STUDENTS]);
int printStudent (Student studentData [MAX_STUDENTS], int whichOne);

