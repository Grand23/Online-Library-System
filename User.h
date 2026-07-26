#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <vector>

class User {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::vector<int> borrowedBooks; // Store IDs of borrowed books


public:
    // Constructor
    User();
    User(std::string username, std::string password, std::string fullName);

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::vector<int> getBorrowedBooks() const;

    // Setters
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setFullName(std::string fullName);

    //Book management
    void borrowBook(int bookId);
    void returnBook(int bookId);
    bool hasBorrowedBook(int bookId) const;
    int getBorrowedCount() const;

    // Display
    void displayInfo() const;

    // File operations
    std::string toString() const;
    static User fromString(const std::string& str);

};

#endif