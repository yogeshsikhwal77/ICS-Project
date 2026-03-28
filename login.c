#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ================ FUNCTION DECLARATIONS ================

// ye functions tere group members banayenge
void studentMenu(Student s);
void teacherMenu(Teacher t);

// login functions
int studentLogin(Student *s);
int teacherLogin(Teacher *t);

// ================= LOGIN FUNCTIONS =================

// Student Login
int studentLogin(Student *s) {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("Error opening students file!\n");
        return 0;
    }

    int id;
    char name[50];

    printf("Enter Student ID: ");
    scanf("%d", &id);

    printf("Enter Name: ");
    scanf(" %[^\n]", name);

    Student temp;

    while (fread(&temp, sizeof(Student), 1, fp)) {
        if (temp.id == id && strcmp(temp.name, name) == 0) {
            *s = temp;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// Teacher Login
int teacherLogin(Teacher *t) {
    FILE *fp = fopen("teachers.dat", "rb");
    if (fp == NULL) {
        printf("Error opening teachers file!\n");
        return 0;
    }

    int id;
    char name[50];

    printf("Enter Teacher ID: ");
    scanf("%d", &id);

    printf("Enter Name: ");
    scanf(" %[^\n]", name);

    Teacher temp;

    while (fread(&temp, sizeof(Teacher), 1, fp)) {
        if (temp.id == id && strcmp(temp.name, name) == 0) {
            *t = temp;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


