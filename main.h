#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define TITLE_LENGTH 100

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;


typedef struct Book {
    int id;
    char title[TITLE_LENGTH];
    char author[50];
    char genre[30];
    int available; 
    time_t borrowTime;
    struct Book *next;
} Book;

extern User users[MAX_USERS];
extern Book *head;
extern int userCount;
extern int bookCount;

extern int loggedIn;
extern int currentUserIndex;
extern int nextBookId;

// توابع
void registerUser();
void loginUser();
void addBook();
void searchBook();
void borrowBook();
void returnBook();
void listAllBooks();
void deleteBook();
void sortBooks();

void saveData();
void loadData();
#endif