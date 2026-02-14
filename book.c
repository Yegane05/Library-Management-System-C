#include "main.h"
#include <time.h>

void addBook() {
    Book *newBook = (Book *)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("Error: Could not allocate memory.\n");
        return;
    }

    newBook->id = nextBookId++;
    newBook->borrowTime = 0;
    newBook->available = 1;

    printf("Enter book title: ");
    fgets(newBook->title, TITLE_LENGTH, stdin);
    newBook->title[strcspn(newBook->title, "\n")] = '\0';

    printf("Enter author: ");
    fgets(newBook->author, 50, stdin);
    newBook->author[strcspn(newBook->author, "\n")] = '\0';

    printf("Enter genre: ");
    fgets(newBook->genre, 30, stdin);
    newBook->genre[strcspn(newBook->genre, "\n")] = '\0';

    newBook->next = head;
    head = newBook;

    bookCount++;
    printf("Book \"%s\" (ID: %d) added successfully.\n", newBook->title, newBook->id);
}

void searchBook() {
    char query[50];
    printf("Enter book title or author name to search: ");
    fgets(query, 50, stdin);
    query[strcspn(query, "\n")] = '\0';

    Book *temp = head;
    int found = 0;
    printf("\n%-5s %-30s %-20s %-15s %-10s\n", "ID", "Title", "Author", "Genre", "Status");
    printf("--------------------------------------------------------------------------------------\n");
    
    while (temp != NULL) {
        if (strstr(temp->title, query) != NULL || strstr(temp->author, query) != NULL) {
            printf("%-5d %-30s %-20s %-15s %-10s\n", 
                   temp->id, temp->title, temp->author, temp->genre, 
                   (temp->available ? "Available" : "Borrowed"));
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No results found for \"%s\".\n", query);
    }
}

void listAllBooks() {
    if (head == NULL) {
        printf("The library is empty.\n");
        return;
    }

    Book *temp = head;
    printf("\n--- Library Book List ---\n");
    printf("%-5s %-25s %-20s %-15s %-10s\n", "ID", "Title", "Author", "Genre", "Status");

    while (temp != NULL) {
        printf("%-5d %-25s %-20s %-15s %-10s\n", 
               temp->id, temp->title, temp->author, temp->genre, 
               temp->available ? "Available" : "Borrowed");
        temp = temp->next;
    }
}

void deleteBook() {
    if (!loggedIn) {
        printf("Please login first.\n");
        return;
    }

    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);
    getchar();

    Book *temp = head;
    Book *prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Book with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    printf("Book \"%s\" (ID: %d) deleted successfully.\n", temp->title, temp->id);
    free(temp);
    bookCount--;
}

void sortBooks() {
    if (head == NULL || head->next == NULL) {
        printf("Not enough books to sort.\n");
        return;
    }

    int swapped;
    Book *ptr1;
    Book *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->title, ptr1->next->title) > 0) {
                Book tempNode;
                
                tempNode.id = ptr1->id;
                strcpy(tempNode.title, ptr1->title);
                strcpy(tempNode.author, ptr1->author);
                strcpy(tempNode.genre, ptr1->genre);
                tempNode.available = ptr1->available;
                tempNode.borrowTime = ptr1->borrowTime;

                ptr1->id = ptr1->next->id;
                strcpy(ptr1->title, ptr1->next->title);
                strcpy(ptr1->author, ptr1->next->author);
                strcpy(ptr1->genre, ptr1->next->genre);
                ptr1->available = ptr1->next->available;
                ptr1->borrowTime = ptr1->next->borrowTime;

                ptr1->next->id = tempNode.id;
                strcpy(ptr1->next->title, tempNode.title);
                strcpy(ptr1->next->author, tempNode.author);
                strcpy(ptr1->next->genre, tempNode.genre);
                ptr1->next->available = tempNode.available;
                ptr1->next->borrowTime = tempNode.borrowTime;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Books sorted alphabetically by title.\n");
}

void checkPenalty(Book *book) {
    if (book->borrowTime != 0) {
        time_t now = time(NULL);
        double days = difftime(now, book->borrowTime) / (60 * 60 * 24);
        if (days > 14) {
            printf("[Penalty] ");
        }
    }
}