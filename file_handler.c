#include "file_handler.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#endif

static int ensure_file_parent_dir(void) {
#ifdef _WIN32
    if (_mkdir("data") == 0) return 1;
#else
    if (mkdir("data", 0777) == 0) return 1;
#endif
    return 1; // ok if already exist
}

int ensure_data_dir(void) {
    return ensure_file_parent_dir();
}

static int load_binary(const char *path, void *arr, size_t itemSize, int max) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    int count = 0;
    while (count < max && fread((char*)arr + count * itemSize, itemSize, 1, fp) == 1) {
        count++;
    }
    fclose(fp);
    return count;
}

int load_students(Student arr[], int max) {
    return load_binary(FILE_STUDENTS, arr, sizeof(Student), max);
}

int save_students(const Student arr[], int count) {
    ensure_data_dir();
    FILE *fp = fopen(FILE_STUDENTS, "wb");
    if (!fp) return 0;
    fwrite(arr, sizeof(Student), count, fp);
    fclose(fp);
    return 1;
}

int load_assignments(Assignment arr[], int max) {
    return load_binary(FILE_ASSIGNMENTS, arr, sizeof(Assignment), max);
}

int load_announcements(Announcement arr[], int max) {
    return load_binary(FILE_ANNOUNCEMENTS, arr, sizeof(Announcement), max);
}

int load_quiz(quiz arr[], int max) {
    return load_binary(FILE_QUIZ, arr, sizeof(quiz), max);
}

Student* find_student(Student arr[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].id == id) return &arr[i];
    }
    return NULL;
}
