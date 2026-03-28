#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_STUDENTS 50
#define MAX_TEACHERS 10
#define MAX_ASSIGNMENT 50
#define MAX_ANNOUNCEMENTS 50
#define MAX_QUIZ 50
#define MAX_OPTIONS 4

#define FILE_STUDENTS      "data/students.dat"
#define FILE_TEACHERS      "data/teachers.dat"
#define FILE_ASSIGNMENTS   "data/assignments.dat"
#define FILE_ANNOUNCEMENTS "data/announcements.dat"
#define FILE_QUIZ          "data/quiz.dat"

typedef struct {
    int id;
    char name[50];
    int totalClasses;
    int attendedClasses;
    float assignmentMarks;
    float quizMarks;
} Student;

typedef struct {
    int id;
    char name[50];
} Teacher;

typedef struct {
    int id;
    int studentId;
    char subject[50];
    char title[100];
    char deadline[20];
    int submitted;
    float marks;
} Assignment;

typedef struct {
    int id;
    char messsage[200];
} Announcement;

typedef struct {
    int id;
    char question[200];
    char option[MAX_OPTIONS][100];
    int correctoption;
} quiz;
#endif 