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
// ----------- ADD ASSIGNMENT (FOR ALL STUDENTS) -----------
void addAssignment() {
    Student students[MAX_STUDENTS];
    int sCount = load_students(students, MAX_STUDENTS);

    if (sCount == 0) {
        printf("No students found! Add students first before creating assignments.\n");
        return;
    }

    int assignId;
    char subject[50], title[100], deadline[20];

    printf("Enter Assignment ID: ");
    scanf("%d", &assignId);

    printf("Enter Subject: ");
    scanf(" %[^\n]", subject);

    printf("Enter Title: ");
    scanf(" %[^\n]", title);

    printf("Enter Deadline (e.g., YYYY-MM-DD): ");
    scanf(" %[^\n]", deadline);

    FILE *fp = fopen(FILE_ASSIGNMENTS, "ab");
    if (fp == NULL) {
        printf("Error opening assignment file!\n");
        return;
    }

    // Create a copy of the assignment for EVERY student automatically
    for (int i = 0; i < sCount; i++) {
        Assignment a;
        a.id = assignId;
        a.studentId = students[i].id; // Assigns it to the current student in the loop
        strcpy(a.subject, subject);
        strcpy(a.title, title);
        strcpy(a.deadline, deadline);
        a.submitted = 0;
        a.marks = 0.0f;

        fwrite(&a, sizeof(Assignment), 1, fp);
    }

    fclose(fp);
    printf("✅ Assignment '%s' added successfully for ALL %d students!\n", title, sCount);
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

// ----------- ADD QUIZ -----------
void addQuiz() {
    FILE *fp = fopen(FILE_QUIZ, "ab");

    if (fp == NULL) {
        printf("Error opening quiz file!\n");
        return;
    }

    quiz q;
    printf("Enter Quiz ID: ");
    scanf("%d", &q.id);

    printf("Enter Question: ");
    scanf(" %[^\n]", q.question);

    for (int i = 0; i < MAX_OPTIONS; i++) {
        printf("Enter Option %d: ", i + 1);
        scanf(" %[^\n]", q.option[i]);
    }

    printf("Enter Correct Option (1-%d): ", MAX_OPTIONS);
    scanf("%d", &q.correctoption);

    fwrite(&q, sizeof(quiz), 1, fp);
    fclose(fp);

    printf("Quiz added successfully!\n");
}

// ----------- ADD STUDENT -----------
void addStudent() {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);

    if (count >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    Student s;
    printf("Enter New Student ID: ");
    scanf("%d", &s.id);

    // Prevent duplicate Student IDs
    if (find_student(students, count, s.id) != NULL) {
        printf("Error: Student ID %d already exists!\n", s.id);
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    // Initialize default values for the new student
    s.totalClasses = 0;
    s.attendedClasses = 0;
    s.assignmentMarks = 0.0f;
    s.quizMarks = 0.0f;

    students[count] = s;
    save_students(students, count + 1);

    printf("Student '%s' added successfully!\n", s.name);
}

// ----------- VIEW ALL STUDENTS -----------
void viewAllStudents() {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);

    if (count == 0) {
        printf("No students found in the database.\n");
        return;
    }

    printf("\n--- Registered Students ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s\n", students[i].id, students[i].name);
    }
}

// ----------- GRADE ASSIGNMENTS -----------
void gradeAssignments() {
    Assignment a[MAX_ASSIGNMENT];
    int count = load_assignments(a, MAX_ASSIGNMENT); 
    
    if (count == 0) {
        printf("No assignments found in the database.\n");
        return;
    }

    int assignId, stuId;
    printf("Enter Assignment ID to grade: ");
    scanf("%d", &assignId);
    
    printf("Enter Student ID to grade: ");
    scanf("%d", &stuId);

    int found = 0;
    for (int i = 0; i < count; i++) {
        // Now checks for BOTH Assignment ID and Student ID
        if (a[i].id == assignId && a[i].studentId == stuId) { 
            found = 1;
            
            if (a[i].submitted == 0) {
                printf("⚠️ Student has not submitted this assignment yet!\n");
                return;
            }

            printf("Grading Assignment: %s (Student ID: %d)\n", a[i].title, a[i].studentId);
            
            printf("Enter marks for this assignment: ");
            scanf("%f", &a[i].marks);

            Student students[MAX_STUDENTS];
            int sCount = load_students(students, MAX_STUDENTS);
            Student *s = find_student(students, sCount, a[i].studentId);
            
            if (s != NULL) {
                s->assignmentMarks += a[i].marks; 
                save_students(students, sCount);
                printf("✅ Student grades updated successfully!\n");
            } else {
                printf("❌ Error: Target student ID not found in database.\n");
            }
            
            break;
        }
    }

    if (!found) {
        printf("❌ Assignment ID or Student ID not found.\n");
    } else {
        FILE *fp = fopen(FILE_ASSIGNMENTS, "wb");
        if (fp != NULL) {
            fwrite(a, sizeof(Assignment), count, fp);
            fclose(fp);
        }
    }
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
        printf("4. Add Quiz\n");
        printf("5. Add New Student\n");
        printf("6. View All Students\n");
        printf("7. Grade Assignment\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: markAttendance(); break;
            case 2: addAssignment(); break;
            case 3: makeAnnouncement(); break;
            case 4: addQuiz(); break;
            case 5: addStudent(); break;
            case 6: viewAllStudents(); break;
            case 7: gradeAssignments(); break;
            case 0:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}