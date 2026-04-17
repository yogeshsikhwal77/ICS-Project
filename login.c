#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// ================= LOGIN FUNCTIONS =================

// Student Login
// Student Login
int studentLogin(Student *s) {
    // FIXED: Using FILE_STUDENTS macro so it looks in the "data" folder
    FILE *fp = fopen(FILE_STUDENTS, "rb");
    if (fp == NULL) {
        printf("Error opening students file! Please run setup first.\n");
        return 0;
    }

    int id;
    char password[50];

    printf("Enter Student ID: ");
    scanf("%d", &id);

    printf("Enter Password: ");
    scanf(" %[^\n]", password);

    Student temp;

    while (fread(&temp, sizeof(Student), 1, fp)) {
        // FIXED: Changed temp.name to temp.password
        if (temp.id == id && strcmp(temp.password, password) == 0) {
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
    // FIXED: Using FILE_TEACHERS macro so it looks in the "data" folder
    FILE *fp = fopen(FILE_TEACHERS, "rb");
    if (fp == NULL) {
        printf("Error opening teachers file! Please run setup first.\n");
        return 0;
    }

    int id;
    char password[50];

    printf("Enter Teacher ID: ");
    scanf("%d", &id);

    printf("Enter Password: ");
    scanf(" %[^\n]", password);

    Teacher temp;

    while (fread(&temp, sizeof(Teacher), 1, fp)) {
        if (temp.id == id && strcmp(temp.password, password) == 0) {
            *t = temp;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}