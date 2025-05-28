#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 50
#define MAX_course_LEN 20
#define MAX_STUDENTS 1000
#define DATA_FILE "students.dat"

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char courseName[MAX_course_LEN];
    double feePaid;
    double balance;
} Student;

extern Student students[MAX_STUDENTS];
extern int studentCount;


void loadData();
void saveData();
void addStudent();
void searchByID();
void searchBycourse();
void sortByBalance();
void sortByFeePaid();
void removeStudent();
void generateReports();
void adminLogin();

#endif
