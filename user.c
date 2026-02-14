#include "main.h"

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    User newUser;
    printf("Enter username: ");
    fgets(newUser.username, USERNAME_LENGTH, stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0';
    printf("Enter password: ");
    fgets(newUser.password, PASSWORD_LENGTH, stdin);
    newUser.password[strcspn(newUser.password, "\n")] = '\0';

    users[userCount++] = newUser;
    printf("User registered successfully.\n");
}

void loginUser() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("Enter password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful.\n");
            loggedIn = 1;
            currentUserIndex = i;
            return;
        }
    }

    printf("Invalid credentials.\n");
}