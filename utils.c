#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void clearScreen() {
    #ifndef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
 
void printLine() {
    printf("============================================================\n");
}

void printHeader(const char *title){
    printLine();
    printf("   %s\n", title);
    printLine();
}
void pressEnter() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}
char gradeFromMarks(float marks){
    if(marks>=90) return 'A';
    else if(marks>=75) return 'B';
    else if(marks>=50) return 'C';
    else if(marks>=35) return 'D';
    else return 'F';
}
void ensureDataDir(){
    #ifndef _WIN32
    system("if not exist data mkdir data");
    #else
    system("");
    #endif
}
int isEligibleForPromotion(Student s) {
    if (s.totalClasses == 0) return 0;
    float pct = (float)s.attendedClasses / s.totalClasses * 100.0f;
    if (pct < 75.0f)            return 0;
    if (s.assignmentMarks < 40) return 0;
    if (s.quizMarks < 40)       return 0;
    return 1;
}
