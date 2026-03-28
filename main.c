#include <stdio.h>
#include "student.h"
#include "file_handler.h"
#include "structs.h"

// Forward declarations (in case not in headers)
int studentLogin(Student *s);
int teacherLogin(Teacher *t);
void studentMenu(int studentId);
void teacherMenu(Teacher t);

int main() {
    int choice;

    // Ensure data folder exists
    ensure_data_dir();

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

                // 👇 use YOUR module
                student_menu(s.id);
            } else {
                printf("Invalid Student Credentials!\n");
            }
        }
        else if (choice == 2) {
            Teacher t;

            if (teacherLogin(&t)) {
                printf("\nLogin Successful! Welcome %s\n", t.name);

                // 👇 your friend’s module
                teacherMenu(t);
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