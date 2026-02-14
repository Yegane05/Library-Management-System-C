# Library Management System in C

A comprehensive Library Management System designed as a semester project for Computer Programming course. This project demonstrates proficiency in **C programming**, **Data Structures (Linked Lists)**, and **File Handling**.

## Features
* **Dynamic Memory Management:** Uses Linked Lists to store books efficiently instead of static arrays.
* **Data Persistence:** Saves and loads data (users and books) using binary files (`.dat`) to keep records after closing the program.
* **User Authentication:** Secure login and registration system for librarians/users.
* **Borrowing System:** Logic to handle borrowing/returning books with automatic penalty calculation for late returns (14-day limit).
* **Search & Sort:** Ability to search books by title/author and sort them alphabetically.

## Project Structure
* `main.c`: Entry point and menu handling.
* `book.c`: Functions related to book management (Add, Search, Sort, Delete).
* `user.c`: User registration and login logic.
* `loan.c`: Borrowing and returning logic.
* `main.h`: Header file containing struct definitions and function prototypes.

## How to Compile
You can compile this project using GCC:
```bash
gcc main.c book.c user.c loan.c -o library_system
