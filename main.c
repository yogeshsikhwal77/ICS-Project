int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT ACADEMIC MANAGEMENT SYSTEM =====\n");
        printf("1. Login as Student\n");
        printf("2. Login as Teacher\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Student s;
            if (studentLogin(&s)) {
                printf("\nLogin Successful! Welcome %s\n", s.name);
                studentMenu(s);   // call student module
            } else {
                printf("Invalid Student Credentials!\n");
            }
        }
        else if (choice == 2) {
            Teacher t;
            if (teacherLogin(&t)) {
                printf("\nLogin Successful! Welcome %s\n", t.name);
                teacherMenu(t);  // call teacher module
            } else {
                printf("Invalid Teacher Credentials!\n");
            }
        }
        else if (choice == 3) {
            printf("Exiting program...\n");
            break;
        }
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
