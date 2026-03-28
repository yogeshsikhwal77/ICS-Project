#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= STRUCTURES =================

typedef struct {
    int id;
    char name[50];
} Student;

typedef struct {
    int id;
    char name[50];
} Teacher;

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

// ================= MAIN FUNCTION =================

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT ACADEMIC MANAGEMENT SYSTEM =====\n");
        printf("1. Login as Student\n");
        printf("2. Login as Teacher\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Student s;
            if (studentLogin(&s)) {
                printf("\nLogin Successful! Welcome %s\n", s.name);
                studentMenu(s);   // call student module
            } else {
                printf("Invalid Student Credentials!\n");
            }
        }
        else if (choice == 2) {
            Teacher t;
            if (teacherLogin(&t)) {
                printf("\nLogin Successful! Welcome %s\n", t.name);
                teacherMenu(t);  // call teacher module
            } else {
                printf("Invalid Teacher Credentials!\n");
            }
        }
        else if (choice == 3) {
            printf("Exiting program...\n");
            break;
        }
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
