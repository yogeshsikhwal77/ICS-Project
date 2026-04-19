# Student Academic Management System

> A console-based C application for managing student academics — attendance, assignments, quizzes, grades, and announcements — with role-based login for Students and Teachers.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Data Structures](#data-structures)
- [Getting Started](#getting-started)
- [Default Accounts](#default-accounts)
- [Usage](#usage)
- [Grade & Attendance Logic](#grade--attendance-logic)
- [Data Storage](#data-storage)
- [Known Limitations](#known-limitations)
- [Future Enhancements](#future-enhancements)
- [Tech Stack](#tech-stack)

---

## Overview

This project is a terminal-based academic management system written in C, inspired by platforms like Google Classroom. It supports two roles — **Student** and **Teacher** — each with their own password-protected login and dedicated menus. All data is persisted using raw binary file I/O, with no external dependencies.

---

## Features

### Student
- View attendance percentage with a low-attendance warning (below 75%)
- View all assigned assignments and their submission status
- Submit pending assignments
- Attempt multiple-choice quizzes — tracks progress and only shows new questions
- View subject-wise grades assigned by the teacher
- View teacher announcements

### Teacher
- Add new students (with ID, name, and password)
- Mark/update attendance for any student
- Create assignments — auto-assigned to every registered student
- Post class-wide announcements
- Add multiple-choice quiz questions (appended incrementally)
- Assign subject-wise letter grades directly to students

---

## Project Structure

```
.
├── main.c              # Entry point and main menu
├── login.c / .h        # Student and teacher login logic
├── student.c / .h      # All student-side features and menu
├── teacher.c / .h      # All teacher-side features and menu
├── file_handler.c / .h # Binary file I/O helpers (load/save)
├── structs.h           # All shared structs, constants, and file path macros
├── setup.c             # One-time seed: creates default accounts
└── data/               # Auto-created at runtime; stores all .dat files
    ├── students.dat
    ├── teachers.dat
    ├── assignments.dat
    ├── announcements.dat
    ├── quiz.dat
    └── grades.dat
```

---

## Data Structures

All structs are defined in `structs.h` and shared across modules.

```c
typedef struct {
    int   id;
    char  name[50];
    char  password[50];
    int   totalClasses;
    int   attendedClasses;
    float assignmentMarks;
    float quizMarks;
    int   lastAttemptedQuestionId;  // tracks quiz progress per student
} Student;

typedef struct {
    int  id;
    char name[50];
    char password[50];
} Teacher;

typedef struct {
    int   id;
    int   studentId;
    char  subject[50];
    char  title[100];
    char  deadline[20];
    int   submitted;
    float marks;
} Assignment;

typedef struct {
    int  id;
    char message[200];
} Announcement;

typedef struct {
    int  id;
    char question[200];
    char option[4][100];
    int  correctoption;
} quiz;

typedef struct {
    int  studentId;
    char subject[50];
    char grade;     // 'A', 'B', 'C', 'D', 'E', or 'F'
} StudentGrade;
```

---

## Getting Started

### Prerequisites

- GCC compiler
  - Windows: [MinGW](https://www.mingw-w64.org/) or [TDM-GCC](https://jmeubank.github.io/tdm-gcc/)
  - Linux/macOS: GCC comes pre-installed or via `sudo apt install gcc` / `xcode-select --install`
- A terminal or command prompt

---

### Step 1 — Run Setup (First Time Only)

Compile and run `setup.c` to create the `data/` directory and seed default accounts:

```bash
# Compile
gcc setup.c file_handler.c -o setup

# Run
./setup        # Linux / macOS
setup.exe      # Windows
```

---

### Step 2 — Compile the Main Program

```bash
gcc main.c login.c student.c teacher.c file_handler.c utils.c -o project
```

### Step 3 — Run

```bash
./project      # Linux / macOS
project.exe    # Windows
```

---

## Default Accounts

Created automatically by running `setup`:

| Role    | ID  | Name           | Password     |
|---------|-----|----------------|--------------|
| Student | 101 | Yogesh         | student123   |
| Teacher | 201 | Admin Teacher  | admin123     |

> You can add more students from the Teacher menu after logging in.

---

## Usage

On launch:

```
===== STUDENT ACADEMIC MANAGEMENT SYSTEM =====
1. Login as Student
2. Login as Teacher
3. Exit
Enter choice:
```

Login requires your **numeric ID** and **password**.

---

### Student Menu

```
===== STUDENT MENU =====
1. View Attendance
2. View Assignments
3. View Grades
4. View Announcements
5. Attempt Quiz
6. Submit Assignment
0. Logout
```

- **Attempt Quiz** — only shows questions added after your last session. Progress is saved automatically.
- **View Grades** — shows subject-wise letter grades assigned by your teacher.

---

### Teacher Menu

```
===== TEACHER MENU =====
1. Mark Attendance
2. Add Assignment
3. Make Announcement
4. Add Quiz
5. Add New Student
6. View All Students
7. Grade
0. Logout
```

- **Add Assignment** — automatically creates a copy of the assignment for every registered student.
- **Add Quiz** — questions are appended; students see new questions on their next attempt.
- **Grade** — assigns a subject-wise letter grade (A–F) to a specific student.

---

## Grade & Attendance Logic

### Attendance

```
Attendance (%) = (Attended Classes / Total Classes) × 100
```

A warning is displayed when attendance falls below **75%**.

### Quiz Scoring

Each quiz session scores the current batch of new questions as a percentage, then averages it into the student's existing quiz score:

```
New Score     = (Correct Answers / Questions Attempted This Session) × 100
Updated Score = (Previous Quiz Score + New Score) / 2
```

### Subject-wise Grades

Grades are entered directly by the teacher per subject:

| Grade | Meaning   |
|-------|-----------|
| A     | Excellent |
| B     | Good      |
| C     | Average   |
| D     | Below Average |
| E     | Poor      |
| F     | Fail      |

---

## Data Storage

All data is stored as raw binary structs in the `data/` directory using `fread` / `fwrite`. The folder is created automatically on first run.

| File                      | Contents              |
|---------------------------|-----------------------|
| `data/students.dat`       | Student records       |
| `data/teachers.dat`       | Teacher records       |
| `data/assignments.dat`    | Assignment records    |
| `data/announcements.dat`  | Announcements         |
| `data/quiz.dat`           | Quiz questions        |
| `data/grades.dat`         | Subject-wise grades   |

> **Note:** Binary files are not human-readable. Do not open them in a text editor. Deleting a `.dat` file will erase all data in that category.

---

## Known Limitations

- No input sanitization — entering non-integer values where integers are expected may cause undefined behavior
- Assignment and quiz IDs must be entered manually; there is no auto-increment
- Duplicate announcement or quiz IDs are not validated
- Grade entries are appended — re-grading the same subject for the same student creates a duplicate entry
- `utils.c` is currently empty (reserved for future helpers)

---

## Future Enhancements

- Auto-increment IDs for assignments, quizzes, and announcements
- Input validation and buffer-safe string handling throughout
- Duplicate detection for grades (update instead of append)
- Subject-wise grade analytics and GPA calculation
- Multi-teacher and multi-class support
- Student self-registration portal
- SQLite or CSV backend for human-readable storage
- GUI frontend (GTK or web-based)

---

## Tech Stack

| Area           | Details                                          |
|----------------|--------------------------------------------------|
| Language       | C (C99 standard)                                 |
| Compiler       | GCC                                              |
| Storage        | Binary flat files via `fread` / `fwrite`         |
| Platform       | Cross-platform — Windows, Linux, macOS           |
| Key Concepts   | Structs, File I/O, Modular design, Role-based access control |
