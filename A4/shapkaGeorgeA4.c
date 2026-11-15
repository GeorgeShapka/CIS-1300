#include "givenA4.h"

#define DEBUG

int readFile(FILE *fPtr, Student studentData[MAX_STUDENTS]){
    int status = 1;
    if(fPtr == NULL){
        status = -1;
    }

    //move position to 2nd line where data starts
    char c;
    do{
        c = fgetc(fPtr);
    }
    while(c != '\n');

    //read data
    int index = 0;
    if(status != 0){
        while(fscanf(fPtr, "%d %s %d", &studentData[index].id, studentData[index].name, &studentData[index].examWeek) == 3){
            for (int i = 0; i < 7; i++){
                fscanf(fPtr, "%lf %lf %lf", &studentData[index].study[i], &studentData[index].breaks[i], &studentData[index].sleep[i]);
            }

            #ifdef DEBUG
                printf("ID: %d\n", studentData[index].id);
                printf("Name: %s\n", studentData[index].name);
                printf("Exam Week: %d\n", studentData[index].examWeek);

                printf("Study Hours: ");
                for (int i = 0; i < 7; i++) {
                    printf("%.2lf ", studentData[index].study[i]);
                }

                printf("\nBreak Hours: ");
                for (int i = 0; i < 7; i++) {
                    printf("%.2lf ", studentData[index].breaks[i]);
                }

                printf("\nSleep Hours: ");
                for (int i = 0; i < 7; i++) {
                    printf("%.2lf ", studentData[index].sleep[i]);
                }

                printf("\n-----------------------------\n");
            #endif
            ++index;
        }
    }
}


void computeStudent (Student * studentData){
    
}


void printClassSummary(Student  [MAX_STUDENTS]){
    
}


void printAtRiskStudents(Student [MAX_STUDENTS]){

}


int printStudent (Student studentData [MAX_STUDENTS], int whichOne){

}