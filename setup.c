#include <stdio.h>
#include "structs.h"
#include "file_handler.h"

int main() {
    // Create the "data" directory if it doesn't exist
    ensure_data_dir();

    // 1. Create a dummy Student account
    Student s1 = {101, "Yogesh Sikhwal", 20, 18, 85.5f, 92.0f};
    
    FILE *fs = fopen(FILE_STUDENTS, "wb");
    if (fs != NULL) {
        fwrite(&s1, sizeof(Student), 1, fs);
        fclose(fs);
        printf("✅ Student account created!\n");
        printf("   -> ID: 101, Name: Yogesh Sikhwal\n");
    } else {
        printf("❌ Failed to create student database.\n");
    }

    // 2. Create a dummy Teacher account
    Teacher t1 = {201, "Admin Teacher"};
    
    FILE *ft = fopen(FILE_TEACHERS, "wb");
    if (ft != NULL) {
        fwrite(&t1, sizeof(Teacher), 1, ft);
        fclose(ft);
        printf("✅ Teacher account created!\n");
        printf("   -> ID: 201, Name: Admin Teacher\n");
    } else {
        printf("❌ Failed to create teacher database.\n");
    }

    printf("\nSetup complete! You can now compile and run your main project.\n");
    return 0;
}