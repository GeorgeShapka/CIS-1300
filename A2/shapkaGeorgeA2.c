/************************shapkaGeorgeA2.c**************
Student Name: George Shapka Email Id: gshapka
Due Date: October ... Course Name: CIS 1300
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:

1) I have read and understood the University policy on academic integrity. 
2) I have completed the Computing with Integrity Tutorial on Moodle; 
and 3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and
all material that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for
this course.
********************************************************/


#include <stdio.h>
#include <stdbool.h>


int main(void){
  const int DaysPerWeek = 7;
  bool doLoop = true;
  char inputYN = 'n';
  int studentCount = 0;
  double weeklyScore = 0.0;
  char letterGrade = 'F';
  int studyMinutes = 0;
  double studyScore = 0.0;
  double averageStudyScore = 0.0;
  double studyContribution = 0.0;
  int breaksTaken = 0;
  double breakScore = 0.0;
  double averageBreakScore = 0.0;
  double breakContribution = 0.0;
  double hoursSleep = 0.0;
  double sleepScore = 0.0;
  double averageSleepScore = 0.0;
  double sleepContribution = 0.0;
  int studyWeight = 0;
  int breakWeight = 0;
  int sleepWeight = 0;
  double allStudentAverageScore = 0.0;


  printf("Welcome to STREAKsafe admin page\n\n");

  //while loop to loop through students
  while(doLoop){
    studentCount++;

    //studyMinutes
    printf("Student# %d:\n", studentCount);
    for(int i = 0; i < DaysPerWeek; i++){
      printf("Day %d study minutes: ", i + 1);
      scanf("%d", &studyMinutes);
      if (studyMinutes > 180){
        studyMinutes = 180;
      }

      studyScore += (studyMinutes / 180.0) * 100.0;
    }
    averageStudyScore = studyScore / DaysPerWeek;
    printf("\n");


    //if the student did not study
    if(averageStudyScore == 0){
      averageBreakScore = 0.0;
      averageSleepScore = 0.0;
    }
    else{
      //breaks
      for(int i = 0; i < DaysPerWeek; i++){
        printf("Day %d breaks taken (0 to 10): ", i + 1);
        scanf("%d", &breaksTaken);

        if(2 <= breaksTaken && breaksTaken <= 4){
          breakScore += 100.0;
        }
        else if(breaksTaken == 1 || breaksTaken == 5){
          breakScore += 70.0;
        }
        else if(breaksTaken == 0 || breaksTaken == 6){
          breakScore += 40.0;
        }
        else if(breaksTaken >= 7){
          breakScore += 10.0;
        }
      }
      averageBreakScore = breakScore / DaysPerWeek;

      //sleep
      printf("\n");
      for(int i = 0; i < DaysPerWeek; i++){
        printf("Night %d sleep hours (0.0 to 12.0): ", i + 1);
        scanf("%lf", &hoursSleep);

        if(7.0 <= hoursSleep && hoursSleep <= 9.0){
          sleepScore += 100.0;
        }
        else if((6.0 <= hoursSleep && hoursSleep <= 7.0) || (9.0 <= hoursSleep && hoursSleep <= 10.0)){
          sleepScore += 70.0;
        }
        else if((5.0 <= hoursSleep && hoursSleep <= 6.0) || (10.0 <= hoursSleep && hoursSleep <= 11.0)){
          sleepScore += 40.0;
        }
        else{
          sleepScore += 10.0;
        }
      }
      averageSleepScore = sleepScore / DaysPerWeek;

      printf("\nIs this an exam week? ('y' or 'n'): ");
      scanf("\n%c", &inputYN);
      printf("\n");
      if(inputYN == 'y'){
        studyWeight = 50;
        breakWeight = 10;
        sleepWeight = 40;
      }
      else if(inputYN == 'n'){
        studyWeight = 40;
        breakWeight = 20;
        sleepWeight = 40;
      }

      //calculate contributions
      studyContribution = (averageStudyScore / 100.0) * studyWeight;
      breakContribution = (averageBreakScore / 100.0) * breakWeight;
      sleepContribution = (averageSleepScore / 100.0) * sleepWeight;

      //calculate grade
      weeklyScore = studyContribution + breakContribution + sleepContribution;
      
      if(sleepContribution < 20.0)
      {
        letterGrade = 'F';
      }
      else if(weeklyScore <= 49.99){
        letterGrade = 'F';
      }
      else if(50 <= weeklyScore && weeklyScore <= 59.99){
        letterGrade = 'D';
      }
      else if(60 <= weeklyScore && weeklyScore <= 69.99){
        letterGrade = 'C';
      }
      else if(70 <= weeklyScore && weeklyScore <= 79.99){
        letterGrade = 'B';
      }
      else if(80 <= weeklyScore){
        letterGrade = 'A';
      }

      printf("Weights: study = %d, breaks = %d, sleep = %d\n\n", studyWeight, breakWeight, sleepWeight);
      printf("Overall study score (%d) = %.2lf / %d\n", studyWeight, studyContribution, studyWeight);
      printf("Overall break score (%d) = %.2lf / %d\n", breakWeight, breakContribution, breakWeight);
      printf("Overall sleep score (%d) = %.2lf / %d\n\n", sleepWeight, sleepContribution, sleepWeight);
    }//end of if study min

    printf("Overall weekly score breakdown\n*************************\nStudy  = %.2lf\nBreaks = %.2lf\nSleep  = %.2lf\n*************************\n", studyContribution, breakContribution, sleepContribution);
    printf("Your overall weekly score = %.2lf%%\n", weeklyScore);
    printf("Overall grade = %c\n\n", letterGrade);

    //add student weekly score to total from all students
    allStudentAverageScore += weeklyScore;


    printf("Would you like to continue: ('y' to continue, 'n' to exit: )");
    scanf("\n%c", &inputYN);//prefixed \n to get trailing newline from scanf to get sleep hours

    //stop the loop if user said no
    if(inputYN == 'n'){
      doLoop = false;
    }

    //reset required variables
    studyScore = 0;
    breakScore = 0;
    sleepScore = 0;
    studyContribution = 0;
    breakContribution = 0;
    sleepContribution = 0;
    weeklyScore = 0;
    studyWeight = 40;
    breakWeight = 20;
    sleepWeight = 40;
    
    printf("\n");
  }
  //get average score
  allStudentAverageScore = allStudentAverageScore / studentCount;

  //output results
  printf("\nAverage weekly score of %d students = %.2lf%%\n\n", studentCount, allStudentAverageScore);
  return(0);
}
