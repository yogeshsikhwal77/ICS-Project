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
        while(1){
            printf("Enter Total Classes: ");
            scanf("%d", &s->totalClasses);
            if(s->totalClasses < 0){
                printf("\ninvaild input");
            }else{
                break;
            }
        }
        while(1){
            printf("Enter Attended Classes: ");
            scanf("%d", &s->attendedClasses);
            if(s->attendedClasses > s->totalClasses || s->attendedClasses < 0){
                printf("\nInvaild Input\n");
            }else{
                break;
            }
        }
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
    printf("Assignment '%s' added successfully for ALL %d students!\n", title, sCount);
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
// teacher.c
// teacher.c
void addQuiz() {
    FILE *fp = fopen(FILE_QUIZ, "ab"); // 'ab' appends new questions to the end
    if (fp == NULL) return;

    int numQuestions;
    while(1){
        printf("How many questions do you want to add? ");
        scanf("%d", &numQuestions);
        if(numQuestions<1){
            printf("\ninvaild input\n");
        }else break;
    }
    for (int k = 0; k < numQuestions; k++) {
        quiz q;
        printf("\n--- Question %d ---\n", k + 1);
        printf("Enter Quiz ID: ");
        scanf("%d", &q.id);
        printf("Enter Question: ");
        scanf(" %[^\n]", q.question);

        for (int i = 0; i < MAX_OPTIONS; i++) {
            printf("Enter Option %d: ", i + 1);
            scanf(" %[^\n]", q.option[i]);
        }

        while(1){printf("\nEnter Correct Option (1-4): \n");
        scanf("%d", &q.correctoption);
        if(q.correctoption > 4 || q.correctoption < 1){
            printf("\ninvaild option\n");

        }else break;
        }

        fwrite(&q, sizeof(quiz), 1, fp);
    }
    fclose(fp);
    printf("\n%d Questions added successfully!\n", numQuestions);
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

    printf("Enter Student Password: ");
    scanf(" %[^\n]", s.password);

    // Initialize default values for the new student
    s.totalClasses = 0;
    s.attendedClasses = 0;
    s.assignmentMarks = 0.0f;
    s.quizMarks = 0.0f;
    s.lastAttemptedQuestionId = 0;

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

void grade() {
    StudentGrade sg;
    
    printf("\n--- Direct Grade Entry ---\n");
    printf("Enter Student ID: ");
    scanf("%d", &sg.studentId);
    
    printf("Enter Subject Name: ");
    scanf(" %[^\n]", sg.subject); // The space before % allows reading strings with spaces
    
    while(1){
        printf("Enter Grade (A, B, C, D, E, F): ");
        scanf(" %c", &sg.grade); // The space before % ignores extra newlines
        if(sg.grade<65 || sg.grade>70){
            printf("invaild input\n");
        }else break;
    }
    // Save directly to a new file called grades.dat
    FILE *fp = fopen("data/grades.dat", "ab");
    if (fp != NULL) {
        fwrite(&sg, sizeof(StudentGrade), 1, fp);
        fclose(fp);
        printf("Grade '%c' for '%s' added successfully to Student %d!\n", sg.grade, sg.subject, sg.studentId);
    } else {
        printf("Error saving grade. Ensure the 'data' folder exists.\n");
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
        printf("7. Grade \n");
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
            case 7: grade(); break;
            case 0:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}