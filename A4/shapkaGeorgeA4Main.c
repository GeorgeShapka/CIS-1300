#include "givenA4.h"
#include <string.h>
#include <ctype.h>

#define INT_DIGITS 9
#define MAX_MENU_INPUT 256
#define MENU_OPTIONS "1234"



int main(void){
    FILE* fPtr = fopen("streaksafe.txt", "r");
    Student students[MAX_STUDENTS];
    char menuInput[MAX_MENU_INPUT] = {0};
    char* menuInputSwitch = 0;
    int doLoop = 1;
    int id = 0;
    char* temp;

    if(fPtr == NULL){
        printf("Error: NULL pointer");
        return(EXIT_FAILURE);
    }

    readFile(fPtr, students);
    // Student s;
    // s.id=7001;
    // s.examWeek = 0;
    // s.study[0] = 90;
    // s.study[1] = 60;
    // s.study[2] = 0;
    // s.study[3] = 180;
    // s.study[4] = 30;
    // s.study[5] = 200;
    // s.study[6] = 0;
    // s.breaks[0] = 2;
    // s.breaks[1] = 0;
    // s.breaks[2] = 3;
    // s.breaks[3] = 5;
    // s.breaks[4] = 2;
    // s.breaks[5] = 7;
    // s.breaks[6] = 1;
    // s.sleep[0] = 7.5;
    // s.sleep[1] = 6;
    // s.sleep[2] = 5.5;
    // s.sleep[3] = 8;
    // s.sleep[4] = 7;
    // s.sleep[5] = 6.5;
    // s.sleep[6] = 9.5;
    // computeStudent(&s);

    for(int i = 0; i < MAX_STUDENTS; i++){
        computeStudent(&students[i]);
    }
    while (doLoop)
    {
        printf("1. Print data for one student, given their id\n");
        printf("2. Print class summary\n");
        printf("3. Print at-risk students\n");
        printf("4. Exit\n");
        if(fgets(menuInput, MAX_MENU_INPUT, stdin) != NULL){
            menuInputSwitch = strchr(MENU_OPTIONS, menuInput[0]);
            switch(menuInputSwitch != NULL ? *menuInputSwitch : 0){
                case '1':
                    printf("Enter Student ID: ");
                    fgets(menuInput, MAX_MENU_INPUT, stdin);
                    id = (int)strtol(menuInput, &temp, 10);
                    if(id > 0){
                        if(printStudent(students, id) == -1){
                            printf("Error reading id\n\n");
                        }
                    }
                    else{
                        printf("Error reading id\n\n");
                    }
                    break;
                case '2':
                    printClassSummary(students);
                    break;
                case '3':
                    printAtRiskStudents(students);
                    break;
                case '4':
                    doLoop = 0;
                    break;
                default:
                    printf("Error reading input, please try again\n\n");
            }
        }
        else{
            perror("Error reading input");
        }
    }

    if(fPtr != NULL){
        fclose(fPtr);
    }

    return(EXIT_SUCCESS);
}