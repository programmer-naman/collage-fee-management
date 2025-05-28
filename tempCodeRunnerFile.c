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