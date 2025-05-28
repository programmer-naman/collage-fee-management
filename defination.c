#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

void clearInputBuffer() {
    while (getchar() != '\n');
}

void loadData() {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        studentCount = 0;
        return;
    }
    fread(&studentCount, sizeof(int), 1, fp);
    fread(students, sizeof(Student), studentCount, fp);
    fclose(fp);
}

void saveData() {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        printf("Error saving data!\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), studentCount, fp);
    fclose(fp);
}


static int findStudentIndexByID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students. Limit reached.\n");
        return;
    }

    Student s;
    printf("Enter Student ID (integer): ");
    if (scanf("%d", &s.id) != 1) {
        printf("Invalid input for ID.\n");
        clearInputBuffer();
        return;
    }
    if (findStudentIndexByID(s.id) != -1) {
        printf("A student with this ID already exists.\n");
        return;
    }

    clearInputBuffer();
    printf("Enter Student Name: ");
    fgets(s.name, MAX_NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter course: ");
    fgets(s.courseName, MAX_course_LEN, stdin);
    s.courseName[strcspn(s.courseName, "\n")] = 0;

    printf("Enter Fee Paid: ");
    if (scanf("%lf", &s.feePaid) != 1 || s.feePaid < 0) {
        printf("Invalid fee paid input.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter Total Fee for course: ");
    double totalFee;
    if (scanf("%lf", &totalFee) != 1 || totalFee < s.feePaid) {
        printf("Invalid total fee input. Must be >= fee paid.\n");
        clearInputBuffer();
        return;
    }

    s.balance = totalFee - s.feePaid;
    students[studentCount++] = s;
    printf("Student added successfully.\n");
    saveData();
}

void searchByID() {
    int id;
    printf("Enter Student ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    int idx = findStudentIndexByID(id);
    if (idx == -1) {
        printf("Student ID %d not found.\n", id);
        return;
    }
    Student s = students[idx];
    printf("ID: %d, Name: %s, course: %s, Fee Paid: %.2lf, Balance: %.2lf\n",
           s.id, s.name, s.courseName, s.feePaid, s.balance);
}

void searchBycourse() {
    char courseName[MAX_course_LEN];
    clearInputBuffer();
    printf("Enter course to search: ");
    fgets(courseName, MAX_course_LEN, stdin);
    courseName[strcspn(courseName, "\n")] = 0;

    int found = 0;
    printf("Students in course %s:\n", courseName);
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].courseName, courseName) == 0) {
            Student s = students[i];
            printf("ID: %d, Name: %s, Fee Paid: %.2lf, Balance: %.2lf\n",
                   s.id, s.name, s.feePaid, s.balance);
            found = 1;
        }
    }
    if (!found)
        printf("No students found in course %s.\n", courseName);
}

int compareByBalance(const void *a, const void *b) {
    return ((Student *)a)->balance - ((Student *)b)->balance;
}

int compareByFeePaid(const void *a, const void *b) {
    return ((Student *)b)->feePaid - ((Student *)a)->feePaid;
}

void sortByBalance() {
    if (studentCount == 0) {
        printf("No student records to sort.\n");
        return;
    }
    qsort(students, studentCount, sizeof(Student), compareByBalance);
    printf("Records sorted by fee balance (ascending):\n");
    for (int i = 0; i < studentCount; i++) {
        Student s = students[i];
        printf("ID:%d, Name:%s, course:%s, Fee Paid:%.2lf, Balance:%.2lf\n",
               s.id, s.name, s.courseName, s.feePaid, s.balance);
    }
}

void sortByFeePaid() {
    if (studentCount == 0) {
        printf("No student records to sort.\n");
        return;
    }
    qsort(students, studentCount, sizeof(Student), compareByFeePaid);
    printf("Records sorted by total fee paid (descending):\n");
    for (int i = 0; i < studentCount; i++) {
        Student s = students[i];
        printf("ID:%d, Name:%s, course:%s, Fee Paid:%.2lf, Balance:%.2lf\n",
               s.id, s.name, s.courseName, s.feePaid, s.balance);
    }
}

void removeStudent() {
    int id;
    printf("Enter Student ID to remove: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    int idx = findStudentIndexByID(id);
    if (idx == -1) {
        printf("Student ID %d not found.\n", id);
        return;
    }
    for (int i = idx; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    printf("Student record removed successfully.\n");
    saveData();
}

void generateReports() {
    double totalFeesCollected = 0;
    double totalPendingDues = 0;
    int studentsWithDues = 0;

    for (int i = 0; i < studentCount; i++) {
        totalFeesCollected += students[i].feePaid;
        totalPendingDues += students[i].balance;
        if (students[i].balance > 0)
            studentsWithDues++;
    }

    printf("\n--- Fee Management Reports ---\n");
    printf("Total Fees Collected: %.2lf\n", totalFeesCollected);
    printf("Total Pending Dues: %.2lf\n", totalPendingDues);
    printf("Number of Students with Outstanding Balances: %d\n", studentsWithDues);

    if (studentsWithDues > 0) {
        printf("\nStudents with Outstanding Balances:\n");
        for (int i = 0; i < studentCount; i++) {
            if (students[i].balance > 0) {
                printf("ID:%d, Name:%s, course:%s, Balance:%.2lf\n",
                       students[i].id, students[i].name, students[i].courseName, students[i].balance);
            }
        }
    } else {
        printf("No outstanding balances.\n");
    }
}