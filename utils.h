#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

void clearScreen();
void printLine();
void printHeader(const char *title);
void pressEnter();
char gradeFromMarks(float marks);
int  isEligibleForPromotion(Student s);
void ensureDataDir();

#endif