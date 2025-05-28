#include <stdio.h>
#include <stdlib.h>
#include "authentication.h"
#include "student.h"



int main() {
    int loginChoice;
    printf("1. Register\n");    
    printf("2. Login\n");
    printf("Enter choice: ");
    scanf("%d", &loginChoice);

    if (loginChoice == 1) {
        registerAdmin();
        return 0;
    } else if (loginChoice == 2) {
        if (!loginAdmin()) {
            printf("Access denied.\n");
            return 1;
        }
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    loadData();

    int choice;
    while (1) {
        printf("\n=== College Fee Management System ===\n");
        printf("1. Add Student Details\n");
        printf("2. Search Student by ID\n");
        printf("3. Search Students by course\n");
        printf("4. Sort Records by Fee Balance\n");
        printf("5. Sort Records by Total Fee Paid\n");
        printf("6. Remove Student Record\n");
        printf("7. Generate Reports\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchByID(); break;
            case 3: searchBycourse(); break;
            case 4: sortByBalance(); break;
            case 5: sortByFeePaid(); break;
            case 6: removeStudent(); break;
            case 7: generateReports(); break;
            case 8: saveData(); printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}