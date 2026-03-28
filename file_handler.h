#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "structs.h"

int ensure_data_dir(void);

int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);

int load_assignments(Assignment arr[], int max);
int load_announcements(Announcement arr[], int max);
int load_quiz(quiz arr[], int max);

Student* find_student(Student arr[], int count, int id);

#endif