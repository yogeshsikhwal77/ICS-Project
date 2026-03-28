#include <stdio.h>
#include "student.h"
#include "file_handler.h"

int main() {
    int studentId;
    int choice;

    // Ensure data folder exists
    ensure_data_dir();

    printf("===== Student Academic Management System =====\n");
    printf("Enter Student ID: ");
    scanf("%d", &studentId);

    do {
        printf("\n===== MENU =====\n");
        printf("1. View Attendance\n");
        printf("2. View Assignments\n");
        printf("3. View Grades\n");
        printf("4. View Announcements\n");
        printf("5. Attempt Quiz\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_attendance(studentId);
                break;
            case 2:
                view_assignments(studentId);
                break;
            case 3:
                view_grades(studentId);
                break;
            case 4:
                view_announcements();
                break;
            case 5:
                attempt_quiz(studentId);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}