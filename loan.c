#include "main.h"

void borrowBook() {
    if (!loggedIn) {
        printf("Please login first.\n");
        return;
    }

    char title[TITLE_LENGTH];
    printf("Enter book title to borrow: ");
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0';

    Book *temp = head;
    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            found = 1;
            if (temp->available == 0) {
                printf("Error: This book is already borrowed.\n");
            } else {
                temp->available = 0;
                temp->borrowTime = time(NULL);
                printf("Book \"%s\" borrowed successfully.\n", temp->title);
            }
            return;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void returnBook() {
    if (!loggedIn) {
        printf("Please login first.\n");
        return;
    }

    char title[TITLE_LENGTH];
    printf("Enter book title to return: ");
    fgets(title, TITLE_LENGTH, stdin);
    title[strcspn(title, "\n")] = '\0';

    Book *temp = head;
    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            found = 1;
            if (temp->available == 1) {
                printf("This book was not borrowed.\n");
                return;
            }

            time_t now = time(NULL);
            double seconds = difftime(now, temp->borrowTime);
            double days = seconds / (60 * 60 * 24);

            if (days > 14) {
                printf("Late return! Penalty: %.2f Toman\n", (days - 14) * 1000);
            }

            temp->available = 1;
            temp->borrowTime = 0;
            printf("Book \"%s\" returned successfully.\n", temp->title);
            return;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Book not found.\n");
    }
}