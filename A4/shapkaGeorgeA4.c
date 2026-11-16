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
    return status;
}


void computeStudent (Student *studentData){
    //calculate study
    for(int i = 0; i < DAYS; i++){
        printf("Day %d study minutes: ", i + 1);
        if(studentData->study[i] > 180){
            studentData->study[i] = 180;
        }

        studentData->studyContribution += (studentData->study[i] / 180.0) * 100.0;
    }
    studentData->studyContribution = studentData->studyContribution / DAYS;


    //if the student did not study
    if(studentData->studyContribution == 0){
      studentData->breakContribution = 0.0;
      studentData->sleepContribution = 0.0;
    }
    else{
        //breaks
        for(int i = 0; i < DAYS; i++){
            if(2 <= studentData->breaks[i] && studentData->breaks[i] <= 4){
            studentData->breakContribution += 100.0;
            }
            else if(studentData->breaks[i] == 1 || studentData->breaks[i] == 5){
            studentData->breakContribution += 70.0;
            }
            else if(studentData->breaks[i] == 0 || studentData->breaks[i] == 6){
            studentData->breakContribution += 40.0;
            }
            else if(studentData->breaks[i] >= 7){
            studentData->breakContribution += 10.0;
            }
        }
        studentData->breakContribution = studentData->breakContribution / DAYS;

        //sleep
        for(int i = 0; i < DAYS; i++){
            if(7.0 <= studentData->sleep[i] && studentData->sleep[i] <= 9.0){
            studentData->sleepContribution += 100.0;
            }
            else if((6.0 <= studentData->sleep[i] && studentData->sleep[i] <= 7.0) || (9.0 <= studentData->sleep[i] && studentData->sleep[i] <= 10.0)){
            studentData->sleepContribution += 70.0;
            }
            else if((5.0 <= studentData->sleep[i] && studentData->sleep[i] <= 6.0) || (10.0 <= studentData->sleep[i] && studentData->sleep[i] <= 11.0)){
            studentData->sleepContribution += 40.0;
            }
            else{
            studentData->sleepContribution += 10.0;
            }
        }
        studentData->sleepContribution = studentData->sleepContribution / DAYS;


        int studyWeight;
        int breakWeight;
        int sleepWeight;
        
        if(studentData->examWeek == 1){
            studyWeight = 50;
            breakWeight = 10;
            sleepWeight = 40;
        }
        else{
            studyWeight = 40;
            breakWeight = 20;
            sleepWeight = 40;
        }

        //calculate contributions
        studentData->studyContribution = (studentData->studyContribution / 100.0) * studyWeight;
        studentData->breakContribution = (studentData->breakContribution / 100.0) * breakWeight;
        studentData->sleepContribution = (studentData->sleepContribution / 100.0) * sleepWeight;

        //calculate grade
        studentData->overallScore = studentData->studyContribution + studentData->breakContribution + studentData->sleepContribution;
        
        if(studentData->sleepContribution < 20.0)
        {
            studentData->grade = 'F';
        }
        else if(studentData->overallScore <= 49.99){
            studentData->grade = 'F';
        }
        else if(50 <= studentData->overallScore && studentData->overallScore <= 59.99){
            studentData->grade = 'D';
        }
        else if(60 <= studentData->overallScore && studentData->overallScore <= 69.99){
            studentData->grade = 'C';
        }
        else if(70 <= studentData->overallScore && studentData->overallScore <= 79.99){
            studentData->grade = 'B';
        }
        else if(80 <= studentData->overallScore){
            studentData->grade = 'A';
        }
    }
}


void printClassSummary(Student  [MAX_STUDENTS]){
    
}


void printAtRiskStudents(Student [MAX_STUDENTS]){

}


int printStudent (Student studentData [MAX_STUDENTS], int whichOne){
    int status = -1;
    
    for(int i = 0; i < MAX_STUDENTS; i++){
        if(studentData[i].id == whichOne){
            status = 1;

            printf("Student Id: %d - Overall weekly score breakdown\n\n", studentData[i].id);
            printf("Student Name: %s\n", studentData[i].name);
            printf("*************************\n");
            printf("Study  = %.2lf\n", studentData[i].studyContribution);
            printf("Breaks = %.2lf\n", studentData[i].breakContribution);
            printf("Sleep  = %.2lf\n", studentData[i].sleepContribution);
            printf("*************************\n");
            printf("Your overall weekly score = %.2lf%%\n", studentData[i].overallScore);
            printf("Overall grade = %c\n", studentData[i].grade);
        }
    }

    return status;
}