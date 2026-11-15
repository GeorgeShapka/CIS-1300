#include "givenA4.h"




int main(void){
    FILE* fPtr = fopen("streaksafe.txt", "r");
    Student students[MAX_STUDENTS];

    if(fPtr == NULL){
        perror("Error");
        return(EXIT_FAILURE);
    }

    readFile(fPtr, students);

    printStudent(students, 1012);

    return(EXIT_SUCCESS);
}