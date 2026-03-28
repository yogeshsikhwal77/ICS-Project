#include "student.h"
#include "file_handler.h"
#include <stdio.h>
#include "structs.h"

static float attendance_pct(const Student *s) {
    if (!s || s->totalClasses <= 0) return 0.0f;
    return (100.0f * s->attendedClasses) / s->totalClasses;
}

static const char* grade_from_marks(float marks) {
    if (marks >= 90) return "A";
    if (marks >= 75) return "B";
    if (marks >= 60) return "C";
    if (marks >= 40) return "D";
    return "Fail";
}

static void update_student_quiz_marks(int studentId, float marks) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    Student *s = find_student(students, count, studentId);
    if (!s) return;
    s->quizMarks = marks;
    save_students(students, count);
}

void attempt_quiz(int studentId) {
    quiz q[MAX_QUIZ]; 
    int count = load_quiz(q, MAX_QUIZ);

    if (count == 0) {
        printf("No quiz available.\n");
        return;
    }

    int score = 0;

    printf("\n--- Quiz ---\n");
    for (int i = 0; i < count; i++) {
        int answer;
        printf("\nQ%d) %s\n", i + 1, q[i].question);

        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("%d. %s\n", j + 1, q[i].option[j]);
        }

        printf("Your answer (1-4): ");
        scanf("%d", &answer);

        if (answer == q[i].correctoption) {   // ✅ FIXED
            score++;
        }
    }

    float marks = (100.0f * score) / count;
    printf("\nQuiz Score: %d/%d\n", score, count);
    printf("Quiz Marks: %.2f\n", marks);

    update_student_quiz_marks(studentId, marks);
}

void view_attendance(int studentId) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    Student *s = find_student(students, count, studentId);

    if (!s) {
        printf("Student not found.\n");
        return;
    }

    float pct = attendance_pct(s);

    printf("\n--- Attendance ---\n");
    printf("Name: %s\n", s->name);
    printf("Total Classes: %d\n", s->totalClasses);
    printf("Attended Classes: %d\n", s->attendedClasses);
    printf("Attendance: %.2f%%\n", pct);

    if (pct < 75.0f) {
        printf("Warning: Attendance below 75%%\n");
    }
}

void view_assignments(int studentId) {
    Assignment a[MAX_ASSIGNMENT];   // ✅ FIXED
    int count = load_assignments(a, MAX_ASSIGNMENT);
    int found = 0;

    printf("\n--- Assignments ---\n");
    for (int i = 0; i < count; i++) {
        if (a[i].studentId == studentId) {
            found = 1;
            printf("ID: %d\n", a[i].id);
            printf("Subject: %s\n", a[i].subject);
            printf("Title: %s\n", a[i].title);
            printf("Deadline: %s\n", a[i].deadline);
            printf("Submitted: %s\n", a[i].submitted ? "Yes" : "No");
            printf("Marks: %.2f\n", a[i].marks);
            printf("---------------------\n");
        }
    }

    if (!found) {
        printf("No assignments found.\n");
    }
}

void view_grades(int studentId) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    Student *s = find_student(students, count, studentId);

    if (!s) {
        printf("Student not found.\n");
        return;
    }

    float total = s->assignmentMarks + s->quizMarks;
    float avg = total / 2.0f;

    printf("\n--- Grades ---\n");
    printf("Assignment Marks: %.2f\n", s->assignmentMarks);
    printf("Quiz Marks: %.2f\n", s->quizMarks);
    printf("Average: %.2f\n", avg);
    printf("Grade: %s\n", grade_from_marks(avg));
}

void view_announcements(void) {
    Announcement a[MAX_ANNOUNCEMENTS];
    int count = load_announcements(a, MAX_ANNOUNCEMENTS);

    printf("\n--- Announcements ---\n");
    if (count == 0) {
        printf("No announcements yet.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", a[i].id, a[i].message);
    }
}