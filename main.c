#include "main.h"

User users[MAX_USERS];
Book *head = NULL;
int userCount = 0;
int bookCount = 0;

int loggedIn = 0;
int currentUserIndex = -1;
int nextBookId = 1;

void saveData() {
    FILE *fu = fopen("users.dat", "wb");
    FILE *fb = fopen("books.dat", "wb");

    if (!fu || !fb) {
        printf("Error saving data.\n");
        if (fu) fclose(fu);
        if (fb) fclose(fb);
        return;
    }

    fwrite(&userCount, sizeof(int), 1, fu);
    fwrite(users, sizeof(User), userCount, fu);

    fwrite(&bookCount, sizeof(int), 1, fb);
    fwrite(&nextBookId, sizeof(int), 1, fb);
    
    Book *temp = head;
    while (temp != NULL) {
        fwrite(temp, sizeof(Book), 1, fb);
        temp = temp->next;
    }

    fclose(fu);
    fclose(fb);
    printf("Data saved successfully.\n");
}

void loadData() {
    FILE *fu = fopen("users.dat", "rb");
    FILE *fb = fopen("books.dat", "rb");

    if (fu) {
        fread(&userCount, sizeof(int), 1, fu);
        fread(users, sizeof(User), userCount, fu);
        fclose(fu);
    }

    if (fb) {
        int savedBookCount;
        fread(&savedBookCount, sizeof(int), 1, fb);
        fread(&nextBookId, sizeof(int), 1, fb);

        for (int i = 0; i < savedBookCount; i++) {
            Book *newBook = (Book *)malloc(sizeof(Book));
            fread(newBook, sizeof(Book), 1, fb);
            
            newBook->next = head;
            head = newBook;
            bookCount++; 
        }
        fclose(fb);
    }
}

int main() {
    loadData();

    while (1) {
        int choice;
        printf("Library Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Add Book\n");
        printf("4. Search Book\n");
        printf("5. Borrow Book\n");
        printf("6. Return Book\n");
        printf("7. List All Books\n");
        printf("8. Delete Book\n");
        printf("9. Sort Books\n");
        printf("0. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                addBook();
                break;
            case 4:
                searchBook();
                break;
            case 5:
                borrowBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                listAllBooks();
                break;
            case 8:
                deleteBook();
                break;
            case 9:
                sortBooks();
                break;
            case 0:
                saveData();
                exit(0);
        }
    }
}