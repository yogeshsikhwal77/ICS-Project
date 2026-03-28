#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"   

// ================= FUNCTIONS =================

// ----------- MARK ATTENDANCE -----------
void markAttendance() {
    FILE *fp = fopen("attendance.dat", "ab");

    if (fp == NULL) {
        printf("Error opening attendance file!\n");
        return;
    }

    Attendance a;

    printf("Enter Student ID: ");
    scanf("%d", &a.studentId);

    printf("Enter Total Classes: ");
    scanf("%d", &a.totalClasses);

    printf("Enter Attended Classes: ");
    scanf("%d", &a.attendedClasses);

    fwrite(&a, sizeof(Attendance), 1, fp);

    fclose(fp);

    printf("Attendance marked successfully!\n");
}

// ----------- ADD ASSIGNMENT -----------
void addAssignment() {
    FILE *fp = fopen("assignments.dat", "ab");

    if (fp == NULL) {
        printf("Error opening assignment file!\n");
        return;
    }

    Assignment a;

    printf("Enter Subject: ");
    scanf(" %[^\n]", a.subject);

    printf("Enter Title: ");
    scanf(" %[^\n]", a.title);

    printf("Enter Deadline: ");
    scanf(" %[^\n]", a.deadline);

    fwrite(&a, sizeof(Assignment), 1, fp);

    fclose(fp);

    printf("Assignment added successfully!\n");
}

// ----------- MAKE ANNOUNCEMENT -----------
void makeAnnouncement() {
    FILE *fp = fopen("announcements.dat", "ab");

    if (fp == NULL) {
        printf("Error opening announcement file!\n");
        return;
    }

    Announcement a;

    printf("Enter Announcement: ");
    scanf(" %[^\n]", a.message);

    fwrite(&a, sizeof(Announcement), 1, fp);

    fclose(fp);

    printf("Announcement added successfully!\n");
}

// ================= TEACHER MENU =================

void teacherMenu(Teacher t) {
    int choice;

    while (1) {
        printf("\n===== TEACHER MENU =====\n");
        printf("Welcome, %s\n", t.name);
        printf("1. Mark Attendance\n");
        printf("2. Add Assignment\n");
        printf("3. Make Announcement\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                markAttendance();
                break;
            case 2:
                addAssignment();
                break;
            case 3:
                makeAnnouncement();
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}
