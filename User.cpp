#include "User.h"
#include <sstream>
#include <algorithm>

User::User() : username(""), password(""), fullName("") {}

User::User(std::string username, std::string password, std::string fullName)
    : username(username), password(password), fullName(fullName) {}

// Getters
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFullName() const { return fullName; }
std::vector<int> User::getBorrowedBooks() const { return borrowedBooks; }

// Setters
void User::setUsername(std::string username) { this->username = username; }
void User::setPassword(std::string password) { this->password = password; }
void User::setFullName(std::string fullName) { this->fullName = fullName; }

void User::borrowBook(int bookId) {
    borrowedBooks.push_back(bookId);
}

void User::returnBook(int bookId) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    }
}

bool User::hasBorrowedBook(int bookId) const {
    return std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) != borrowedBooks.end();
}

int User::getBorrowedCount() const {
    return borrowedBooks.size();
}

void User::displayInfo() const {
    std::cout << "\n--- User Information ---\n";
    std::cout << "Username: " << username << "\n";
    std::cout << "Full Name: " << fullName << "\n";
    std::cout << "Borrowed Books: " << borrowedBooks.size() << "\n";
    if (!borrowedBooks.empty()) {
        std::cout<< "Borrowed Book IDs: ";
        for (int id : borrowedBooks) {
            std::cout << id << " ";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------\n";
}

std::string User::toString() const {
    std::ostringstream oss;
    oss << username << "|" << password << "|" << fullName << "|";
    for (size_t i = 0; i < borrowedBooks.size(); ++i) {
        if (i > 0) oss << ",";
        oss << borrowedBooks[i];
    }
    return oss.str();
}

User User::fromString(const std::string& str ) {
    std::istringstream iss(str);
    std::string token;
    User user;

    std::getline(iss, token, '|');
    user.username = token;

    std::getline(iss, token, '|');
    user.password = token;

    std::getline(iss, token, '|');
    user.fullName = token;

    //Parse borrowed book
    if (std::getline(iss, token)) {
        if (!token.empty()) {
            std::istringstream bookStream(token);
            std::string bookId;
            while (std::getline(bookStream, bookId, ',')) {
                if (!bookId.empty()) {
                    user.borrowedBooks.push_back(std::stoi(bookId));
                }
            }
        }
    }

    return user;
}
