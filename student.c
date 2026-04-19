#include "student.h"
#include "file_handler.h"
#include <stdio.h>
#include "structs.h"

static float attendance_pct(const Student *s)
{
    if (!s || s->totalClasses <= 0)
        return 0.0f;
    return (100.0f * s->attendedClasses) / s->totalClasses;
}



// student.c
void attempt_quiz(int studentId) {
    quiz q[MAX_QUIZ];
    int count = load_quiz(q, MAX_QUIZ);
    
    Student students[MAX_STUDENTS];
    int student_count = load_students(students, MAX_STUDENTS);
    Student *s = find_student(students, student_count, studentId);

    if (count == 0 || !s) {
        printf("No new quizzes available.\n");
        return;
    }

    int new_questions_found = 0;
    int correct_answers = 0;
    int total_attempted_now = 0;

    printf("\n--- New Questions for You ---\n");
    for (int i = 0; i < count; i++) {
        // Only show questions the student hasn't seen yet
        if (q[i].id > s->lastAttemptedQuestionId) {
            new_questions_found = 1;
            int answer;

            printf("\nQ%d) %s\n", q[i].id, q[i].question);
            for (int j = 0; j < MAX_OPTIONS; j++) {
                printf("%d. %s\n", j + 1, q[i].option[j]);
            }

            while(1){
                printf("Your answer (1-4): ");
                scanf("%d", &answer);
                if(answer > 4 || answer < 1){
                    printf("invaild input\n");
                }else{
                    break;
                }
            }
            if (answer == q[i].correctoption) {
                correct_answers++;
            }
            
            total_attempted_now++;
            // Update the last attempted ID to this question
            s->lastAttemptedQuestionId = q[i].id;
        }
    }

    if (!new_questions_found) {
        printf("You are all caught up! No new questions from the teacher.\n");
        return;
    }

    // Update marks: cumulative logic or per-session
    // Example: adding new marks to existing total
    float session_marks = (100.0f * correct_answers) / total_attempted_now;
    s->quizMarks = (s->quizMarks + session_marks) / 2.0f; 

    save_students(students, student_count);
    printf("\n Progress saved! Your new average score: %.2f\n", s->quizMarks);
}
// ----------- SUBMIT ASSIGNMENT -----------
void submit_assignment(int studentId)
{
    Assignment a[MAX_ASSIGNMENT];
    int count = load_assignments(a, MAX_ASSIGNMENT);
    int found = 0;

    printf("\n--- Pending Assignments ---\n");
    for (int i = 0; i < count; i++)
    {
        if (a[i].studentId == studentId && a[i].submitted == 0)
        {
            printf("ID: %d | Subject: %s | Title: %s\n", a[i].id, a[i].subject, a[i].title);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No pending assignments to submit.\n");
        return;
    }

    int assignId;
    printf("Enter Assignment ID to submit: ");
    scanf("%d", &assignId);

    int submitted_success = 0;
    for (int i = 0; i < count; i++)
    {
        if (a[i].id == assignId && a[i].studentId == studentId)
        {
            a[i].submitted = 1; // Change submission status
            submitted_success = 1;
            break;
        }
    }

    if (submitted_success)
    {
        FILE *fp = fopen(FILE_ASSIGNMENTS, "wb");
        if (fp != NULL)
        {
            fwrite(a, sizeof(Assignment), count, fp);
            fclose(fp);
            printf("Assignment submitted successfully!\n");
        }
    }
    else
    {
        printf("Invalid Assignment ID.\n");
    }
}

void view_attendance(int studentId)
{
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    Student *s = find_student(students, count, studentId);

    if (!s)
    {
        printf("Student not found.\n");
        return;
    }

    float pct = attendance_pct(s);

    printf("\n--- Attendance ---\n");
    printf("Name: %s\n", s->name);
    printf("Total Classes: %d\n", s->totalClasses);
    printf("Attended Classes: %d\n", s->attendedClasses);
    printf("Attendance: %.2f%%\n", pct);

    if (pct < 75.0f)
    {
        printf("Warning: Attendance below 75%%\n");
    }
}

void view_assignments(int studentId)
{
    Assignment a[MAX_ASSIGNMENT]; 
    int count = load_assignments(a, MAX_ASSIGNMENT);
    int found = 0;

    printf("\n--- Assignments ---\n");
    for (int i = 0; i < count; i++)
    {
        if (a[i].studentId == studentId)
        {
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

    if (!found)
    {
        printf("No assignments found.\n");
    }
}

void view_announcements(void) {
    Announcement a[MAX_ANNOUNCEMENTS];
    int count = load_announcements(a, MAX_ANNOUNCEMENTS);

    printf("\n--- Announcements ---\n");
    if (count == 0) {
        printf("No new announcements from the teacher.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID: %d\n", a[i].id);
        printf("Message: %s\n", a[i].message);
        printf("--------------------------------------------------\n");
    }
}

void view_grades(int studentId) {
    FILE *fp = fopen("data/grades.dat", "rb");
    if (fp == NULL) {
        printf("\nNo grades have been published yet.\n");
        return;
    }

    StudentGrade sg;
    int found = 0;

    printf("\n--- Your Subject Grades ---\n");
    printf("%-20s | %s\n", "SUBJECT", "GRADE");
    printf("------------------------------- \n");

    // Read through the file and print grades that match this student's ID
    while (fread(&sg, sizeof(StudentGrade), 1, fp)) {
        if (sg.studentId == studentId) {
            printf("%-20s |   %c\n", sg.subject, sg.grade);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No grades have been assigned to your ID yet.\n");
    }
    printf("------------------------------- \n");
}

// Add this at the end of student.c

void student_menu(int studentId)
{
    int choice;
    while (1)
    {
        printf("\n===== STUDENT MENU =====\n");
        printf("1. View Attendance\n");
        printf("2. View Assignments\n");
        printf("3. View Grades\n");
        printf("4. View Announcements\n");
        printf("5. Attempt Quiz\n");
        printf("6. Submit Assignment\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        
        // Check if scanf successfully read exactly 1 integer
        if (scanf("%d", &choice) != 1) 
        {
            // Clear the invalid input from the buffer
            while (getchar() != '\n'); 
            printf("Invalid input! Please enter a valid number.\n");
            continue; // Skip the switch statement and show the menu again
        }

        switch (choice)
        {
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
        case 6:
            submit_assignment(studentId);
            break;
        case 0:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}