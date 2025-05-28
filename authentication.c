#include <stdio.h>
#include <string.h>
#include "authentication.h"

void registerAdmin() {
    char user[70], pass[70];
    FILE *ff = fopen("ss.txt", "a");

    if (ff == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter new username: ");
    scanf(" %[^\n]", user);
    printf("Enter new password: ");
    scanf(" %[^\n]", pass);

    fprintf(ff, "%s:%s\n", user, pass);
    fclose(ff);
    printf("Admin registered.\n");
}

int loginAdmin() {
    char user[70], pass[70];
    char line[150]; 
    int found = 0;

    FILE *ff = fopen("ss.txt", "r");

    if (ff == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    printf("Enter username: ");
    scanf(" %[^\n]", user);
    printf("Enter password: ");
    scanf(" %[^\n]", pass);

    while (fgets(line, sizeof(line), ff)) {
        line[strcspn(line, "\n")] = '\0';

        char *saveduser = strtok(line, ":");
        char *savedpass = strtok(NULL, "\n");

        if (saveduser && savedpass &&
            strcmp(user, saveduser) == 0 &&
            strcmp(pass, savedpass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(ff);

    if (found) {
        printf("Login successful.\n");
        return 1;
    } else {
        printf("Invalid username or password.\n");
        return 0;
    }
}
