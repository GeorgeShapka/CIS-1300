#include <stdio.h>
#include <stdbool.h>


int main(void){
  const int DaysPerWeek = 7;
  bool doLoop = true;
  char inputYN = 'n';
  int studentCount = 0;
  double averageScore = 0.0;
  int studyMinutes = 0;
  double studyScore = 0.0;
  double averageStudyScore = 0.0;
  int breaksTaken = 0;
  double breakScore = 0.0;
  double averageBreakScore = 0.0;
  double hoursSleep = 0.0;
  double sleepScore = 0.0;
  double averageSleepScore = 0.0;
  int studyWeight = 0;
  int breakWeight = 0;
  int sleepWeight = 0;


  //while loop to loop through students
  while(doLoop){
    studentCount++;
    printf("Welcome to STREAKsafe admin page\n\nStudent#%d:", studentCount);

    //studyMinutes
    printf("\n");
    for(int i = 0; i < DaysPerWeek; i++){
      printf("Day <%d> study minutes: ", i + 1);
      scanf("%d", &studyMinutes);
      if (studyMinutes > 180){
        studyMinutes = 180;
      }

      studyScore += (studyMinutes / 180.0) * 100.0;
    }
    averageStudyScore = studyScore / DaysPerWeek;


    //if the student did not study
    if(studyMinutes == 0){
      averageBreakScore = 0.0;
      averageSleepScore = 0.0;
    }
    else{
      //breaks
      printf("\n");
      for(int i = 0; i < DaysPerWeek; i++){
        printf("Day <%d> breaks taken (0 to 10): ", i + 1);
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
        printf("Night <%d> sleep hours (0.0 to 12.0); ", i + 1);
        scanf("%lf", &hoursSleep);

        if(7.0 <= hoursSleep && hoursSleep <= 9.0){
          sleepScore += 100.0;
        }
        else if((6.0 <= hoursSleep && hoursSleep <= 7.0) || (9.0 <= hoursSleep && hoursSleep <= 10.0)){
          sleepScore += 70.0;
        }
        else if((5.0 <= hoursSleep && hoursSleep <= 6.0) || (10.0 <= hoursSleep && hoursSleep <= 11.0)){
          sleepScore += 70.0;
        }
        else{
          sleepScore += 10.0;
        }
      }
      averageSleepScore = sleepScore / DaysPerWeek;

      printf("Is this an exam week? ('y' or 'n'): ");
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

      printf("Weights: study = %d, breaks = %d, sleep = %d\n", studyWeight, breakWeight, sleepWeight);
    }//end of if study min

      printf("Overall study score (%d) = %.2lf / %d\n", studyWeight, studyScore, studyWeight);
      printf("Overall break score (%d) = %.2lf / %d\n", breakWeight, breakScore, breakWeight);
      printf("Overall sleep score (%d) = %.2lf / %d\n\n", sleepWeight, sleepScore, sleepWeight);

      printf("aaa");

    averageScore = (studyScore + sleepScore + breakScore) / 3;


    printf("Would you like to continue: ('y' to continue, 'n' to exit: )");
    scanf("\n%c", &inputYN);//prefixed \n to get trailing newline from scanf to get sleep hours

    //stop the loop if user said no
    if(inputYN == 'n'){
      doLoop = false;
    }

    //reset variables
    studyScore = 0;
    breakScore = 0;
    sleepScore = 0;
  }

  //output results
  printf("Average weekly score of %d students - %.2lf%%\n", studentCount, averageScore);
  return(0);
}
