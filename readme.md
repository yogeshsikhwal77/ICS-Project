# Student Academic Management System

A console-based academic management application written in C, inspired by platforms like Google Classroom. It supports two user roles — **Teacher** and **Student** — with role-based menus, binary file storage, and automatic grade/attendance calculations.

---

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Data Structures](#data-structures)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Grade & Attendance Logic](#grade--attendance-logic)
- [Data Storage](#data-storage)
- [Future Enhancements](#future-enhancements)

---

## Features

**Student**
- View attendance with percentage and low-attendance warning
- View assigned assignments and submission status
- Submit assignments
- View grades (assignment + quiz average) with letter grade
- View teacher announcements
- Attempt multiple-choice quizzes (one attempt only)

**Teacher**
- Add and manage students
- Mark attendance for any student
- Create assignments (auto-assigned to all students)
- Grade submitted assignments
- Post announcements
- Create multiple-choice quizzes

---

## Project Structure

```
.
├── main.c              # Entry point, main menu
├── login.c / .h        # Student and teacher login logic
├── student.c / .h      # All student-side features
├── teacher.c / .h      # All teacher-side features
├── file_handler.c / .h # Binary file I/O helpers
├── structs.h           # All shared structs and constants
├── setup.c             # One-time setup: creates sample accounts
├── utils.c / .h        # Utility helpers (reserved)
└── data/               # Auto-created at runtime
    ├── students.dat
    ├── teachers.dat
    ├── assignments.dat
    ├── announcements.dat
    └── quiz.dat
```

---

## Data Structures

```c
// Student
typedef struct {
    int   id;
    char  name[50];
    int   totalClasses;
    int   attendedClasses;
    float assignmentMarks;
    float quizMarks;
} Student;

// Teacher
typedef struct {
    int  id;
    char name[50];
} Teacher;

// Assignment
typedef struct {
    int   id;
    int   studentId;
    char  subject[50];
    char  title[100];
    char  deadline[20];
    int   submitted;
    float marks;
} Assignment;

// Announcement
typedef struct {
    int  id;
    char message[200];
} Announcement;

// Quiz
typedef struct {
    int  id;
    char question[200];
    char option[4][100];
    int  correctoption;
} quiz;
```

---

## Getting Started

### Prerequisites

- GCC compiler (MinGW on Windows, or native on Linux/macOS)
- A terminal / command prompt

### 1. Compile the Setup Program

```bash
gcc setup.c file_handler.c -o setup
./setup          # Linux/macOS
setup.exe        # Windows
```

This creates the `data/` folder and seeds one student and one teacher account:

| Role    | ID  | Name           |
|---------|-----|----------------|
| Student | 101 | Yogesh Sikhwal  |
| Teacher | 201 | Admin Teacher  |

### 2. Compile the Main Program

```bash
gcc main.c login.c student.c teacher.c file_handler.c utils.c -o project
./project        # Linux/macOS
project.exe      # Windows
```

---

## Usage

On launch you will see:

```
===== STUDENT ACADEMIC MANAGEMENT SYSTEM =====
1. Login as Student
2. Login as Teacher
3. Exit
```

**Student login** — enter your ID and full name.  
**Teacher login** — enter your ID and full name.

### Student Menu

```
1. View Attendance
2. View Assignments
3. View Grades
4. View Announcements
5. Attempt Quiz
6. Submit Assignment
0. Logout
```

### Teacher Menu

```
1. Mark Attendance
2. Add Assignment
3. Make Announcement
4. Add Quiz
5. Add New Student
6. View All Students
7. Grade Assignment
0. Logout
```

---

## Grade & Attendance Logic

### Attendance

```
Attendance % = (Attended Classes / Total Classes) × 100
```

A warning is shown when attendance falls below **75%**.

### Grade Calculation

Average = (Assignment Marks + Quiz Marks) / 2

| Average Score | Grade |
|---------------|-------|
| 90 and above  | A     |
| 75 – 89       | B     |
| 60 – 74       | C     |
| 40 – 59       | D     |
| Below 40      | Fail  |

### Promotion Eligibility

A student is eligible for promotion if:
- Attendance ≥ 75%
- No failed subjects

---

## Data Storage

All data is stored as raw binary files inside the `data/` directory using `fread`/`fwrite` on C structs. The directory is created automatically on first run.

| File                     | Contents            |
|--------------------------|---------------------|
| `data/students.dat`      | Student records     |
| `data/teachers.dat`      | Teacher records     |
| `data/assignments.dat`   | Assignment records  |
| `data/announcements.dat` | Announcements       |
| `data/quiz.dat`          | Quiz questions      |

---

## Future Enhancements

- Password-protected login
- Graphical User Interface (GUI)
- Database backend (SQLite)
- Subject-wise grade analytics
- Multi-teacher / multi-class support
- Student self-registration portal

---

## Technologies Used

| Area              | Details                        |
|-------------------|--------------------------------|
| Language          | C (C99)                        |
| Compiler          | GCC                            |
| Storage           | Binary files via file handling |
| Platform          | Windows / Linux / macOS        |
| IDE               | VS Code (terminal-based)       |
| Key Concepts      | Structs, File I/O, Modular programming, Role-based access |
