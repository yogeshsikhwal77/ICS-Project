#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"
#include "structs.h"
#include "file_handler.h" // Needed to load and save students

// ----------- MARK ATTENDANCE -----------
void markAttendance() {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    
    if (count == 0) {
        printf("No students found in the database.\n");
        return;
    }

    int sId;
    printf("Enter Student ID: ");
    scanf("%d", &sId);

    Student *s = find_student(students, count, sId);
    if (s != NULL) {
        printf("Enter Total Classes: ");
        scanf("%d", &s->totalClasses);

        printf("Enter Attended Classes: ");
        scanf("%d", &s->attendedClasses);

        save_students(students, count);
        printf("Attendance updated successfully!\n");
    } else {
        printf("Student not found!\n");
    }
}

// ----------- ADD ASSIGNMENT -----------
void addAssignment() {
    FILE *fp = fopen(FILE_ASSIGNMENTS, "ab");

    if (fp == NULL) {
        printf("Error opening assignment file!\n");
        return;
    }

    Assignment a;
    
    printf("Enter Assignment ID: ");
    scanf("%d", &a.id);
    
    printf("Enter Target Student ID: ");
    scanf("%d", &a.studentId);

    printf("Enter Subject: ");
    scanf(" %[^\n]", a.subject);

    printf("Enter Title: ");
    scanf(" %[^\n]", a.title);

    printf("Enter Deadline (e.g., YYYY-MM-DD): ");
    scanf(" %[^\n]", a.deadline);
    
    a.submitted = 0;
    a.marks = 0.0f;

    fwrite(&a, sizeof(Assignment), 1, fp);
    fclose(fp);

    printf("Assignment added successfully!\n");
}

// ----------- MAKE ANNOUNCEMENT -----------
void makeAnnouncement() {
    FILE *fp = fopen(FILE_ANNOUNCEMENTS, "ab");

    if (fp == NULL) {
        printf("Error opening announcement file!\n");
        return;
    }

    Announcement a;
    
    printf("Enter Announcement ID: ");
    scanf("%d", &a.id);

    printf("Enter Announcement Message: ");
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