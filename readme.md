student Academic Management System 

 

 

1. Introduction 

 

The Student Academic Management System is a console-based application developed using C language. 

The system is inspired by platforms like Google Classroom and is designed to manage academic activities within a school environment. 

 

The system provides two types of users: 

 

Teacher 

 

Student 

 

Each user has role-based access and functionalities. 

 

The system uses file handling to store and manage data permanently. 

 

2. Objective of the Project 

 

The main objective of this project is: 

 

To create a role-based academic management system. 

 

To automate attendance tracking. 

 

To manage assignments and grading. 

 

To provide announcement and quiz features. 

 

To implement real-world school logic using C programming and file handling. 

 

3. Technologies Used 

 

Programming Language: C 

 

Concepts Used: 

 

Structures 

 

File Handling (Binary Files) 

 

Functions 

 

Conditional Statements 

 

Loops 

 

Role-Based Access Control 

 

Compiler: GCC 

 

Platform: VS Code (Terminal-based execution) 

 

4. System Architecture Overview 

 

The system works in the following flow: 

 

User selects role (Teacher / Student) 

 

Login using ID and Name 

 

Role-based menu is displayed 

 

User performs operations 

 

Data is stored and retrieved using binary files 

 

The system is fully console-based and file-driven. 

 

5. Functional Modules 

5.1 Login Module 

 

User selects: 

 

Login as Teacher 

 

Login as Student 

 

Login verification using: 

 

ID 

 

Name 

 

Role-based access is provided after successful login. 

 

5.2 Student Module 

 

After login, a student can: 

 

1. View Attendance 

 

Total classes 

 

Attended classes 

 

Attendance percentage (auto-calculated) 

 

Warning if attendance is below 75% 

 

2. View Assignments 

 

Assignment title 

 

Subject 

 

Deadline 

 

Submission status 

 

3. View Grades 

 

Assignment marks 

 

Quiz marks 

 

Grade (Auto-calculated) 

 

4. View Announcements 

 

Teacher announcements displayed from file 

 

5. Attempt Quiz 

 

Multiple choice questions 

 

Auto result calculation 

 

5.3 Teacher Module 

 

After login, a teacher can: 

 

1. Mark Attendance 

 

Select student 

 

Mark Present / Absent 

 

Attendance updated in file 

 

2. Add Assignment 

 

Subject name 

 

Assignment title 

 

Deadline 

 

Stored in assignment file 

 

3. Grade Assignments 

 

Enter marks for students 

 

Grade automatically calculated 

 

4. Make Announcement 

 

Add announcement message 

 

Visible to all students 

 

5. Conduct Quiz 

 

Add question 

 

Add 4 options 

 

Set correct answer 

 

Stored in quiz file 

 

6. Data Storage Structure 

 

The system uses binary files for permanent storage. 

 

Files used: 

 

students.dat 

 

teachers.dat 

 

attendance.dat 

 

assignments.dat 

 

announcements.dat 

 

quiz.dat 

 

Each file stores structured data using C structures. 

 

7. Data Structures Used 

 

Example: 

 

Student Structure 

 

ID 

 

Name 

 

Total Classes 

 

Attended Classes 

 

Assignment Marks 

 

Quiz Marks 

 

Teacher Structure 

 

ID 

 

Name 

 

Assignment Structure 

 

Subject 

 

Title 

 

Deadline 

 

Announcement Structure 

 

Message 

 

Quiz Structure 

 

Question 

 

Options 

 

Correct Answer 

 

8. Key Functional Logic 

Attendance Calculation 

 

Attendance % = 

(Attended Classes / Total Classes) × 100 

 

If attendance < 75% 

→ Warning displayed. 

 

Grade Calculation 

 

Based on marks: 

 

90+ → A 

 

75–89 → B 

 

60–74 → C 

 

40–59 → D 

 

Below 40 → Fail 

 

Promotion Logic 

 

Student is eligible for promotion if: 

 

Attendance ≥ 75% 

 

No failed subjects 

 

9. Features of the Project 

 

Role-Based Login System 

 

Academic Record Management 

 

Attendance Tracking System 

 

Assignment Management 

 

Automatic Grade Calculation 

 

Announcement System 

 

Basic Quiz System 

 

File-Based Permanent Storage 

 

10. Future Enhancements 

 

Graphical User Interface 

 

Database Integration 

 

Password Protection 

 

Subject-wise Analytics 

 

Multi-user environment 

 

11. Conclusion 

 

This project demonstrates the implementation of a real-world academic management system using C language. 

It applies core programming concepts such as structures, file handling, modular programming, and logical processing. 

 

The system is designed to simulate a simplified classroom management platform in a console-based environment. 