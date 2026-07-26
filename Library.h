#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;
    int nextBookId;
    User* currentUser;
    
    // File operations
    void loadBooks();
    void saveBooks();
    void loadUsers();
    void saveUsers();
    
public:
    Library();
    ~Library();
    
    // Book management
    void addBook();
    void removeBook();
    void searchBook();
    void displayAllBooks();
    void displayAvailableBooks();
    
    // User management
    void registerUser();
    bool loginUser();
    void logoutUser();
    void displayCurrentUser();
    
    // Borrowing operations
    void borrowBook();
    void returnBook();
    
    // Menu
    void mainMenu();
    void userMenu();
    
    // Getters
    User* getCurrentUser() const { return currentUser; }
};

#endif