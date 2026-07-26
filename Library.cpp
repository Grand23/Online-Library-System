#include "Library.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <limits>
#include <conio.h> // For password masking on Windows

Library::Library() : nextBookId(1), currentUser(nullptr) {
    loadBooks();
    loadUsers();
    if (!books.empty()) {
        nextBookId = books.back().getId() + 1;
    }
}

Library::~Library() {
    saveBooks();
    saveUsers();
}

void Library::loadBooks() {
    std::ifstream file("books.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                books.push_back(Book::fromString(line));
            }
        }
        file.close();
    }
}

void Library::saveBooks() {
    std::ofstream file("books.txt");
    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.toString() << "\n";
        }
        file.close();
    }
}

void Library::loadUsers() {
    std::ifstream file("users.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                users.push_back(User::fromString(line));
            }
        }
        file.close();
    }
}

void Library::saveUsers() {
    std::ofstream file("users.txt");
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.toString() << "\n";
        }
        file.close();
    }
}

void Library::addBook() {
    std::string title, author, isbn;
    
    std::cout << "\n--- Add New Book ---\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    
    std::cout << "Enter author: ";
    std::getline(std::cin, author);
    
    std::cout << "Enter ISBN: ";
    std::getline(std::cin, isbn);
    
    Book newBook(nextBookId++, title, author, isbn);
    books.push_back(newBook);
    
    std::cout << "Book added successfully with ID: " << newBook.getId() << "\n";
    saveBooks();
}

void Library::removeBook() {
    int id;
    std::cout << "\n--- Remove Book ---\n";
    std::cout << "Enter book ID to remove: ";
    std::cin >> id;
    
    auto it = std::find_if(books.begin(), books.end(), 
        [id](const Book& b) { return b.getId() == id; });
    
    if (it != books.end()) {
        if (!it->getIsAvailable()) {
            std::cout << "Cannot remove book. It is currently borrowed.\n";
            return;
        }
        books.erase(it);
        std::cout << "Book removed successfully.\n";
        saveBooks();
    } else {
        std::cout << "Book not found.\n";
    }
}

void Library::searchBook() {
    std::string searchTerm;
    std::cout << "\n--- Search Book ---\n";
    std::cout << "Enter title or author to search: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, searchTerm);
    
    // Convert search term to lowercase for case-insensitive search
    std::string lowerSearch = searchTerm;
    std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
    
    bool found = false;
    for (const auto& book : books) {
        std::string lowerTitle = book.getTitle();
        std::string lowerAuthor = book.getAuthor();
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
        std::transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
        
        if (lowerTitle.find(lowerSearch) != std::string::npos || 
            lowerAuthor.find(lowerSearch) != std::string::npos) {
            book.displayInfo();
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No books found matching your search.\n";
    }
}

void Library::displayAllBooks() {
    std::cout << "\n--- All Books ---\n";
    if (books.empty()) {
        std::cout << "No books in the library.\n";
        return;
    }
    
    for (const auto& book : books) {
        book.displayInfo();
    }
}

void Library::displayAvailableBooks() {
    std::cout << "\n--- Available Books ---\n";
    bool found = false;
    for (const auto& book : books) {
        if (book.getIsAvailable()) {
            book.displayInfo();
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No books available at the moment.\n";
    }
}

void Library::registerUser() {
    std::string username, password, fullName;
    
    std::cout << "\n--- User Registration ---\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    
    // Check if username already exists
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const User& u) { return u.getUsername() == username; });
    
    if (it != users.end()) {
        std::cout << "Username already exists. Please choose another.\n";
        return;
    }
    
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    
    std::cout << "Enter full name: ";
    std::getline(std::cin, fullName);
    
    users.push_back(User(username, password, fullName));
    std::cout << "Registration successful!\n";
    saveUsers();
}

bool Library::loginUser() {
    std::string username, password;
    
    std::cout << "\n--- User Login ---\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    
    auto it = std::find_if(users.begin(), users.end(),
        [&username, &password](const User& u) {
            return u.getUsername() == username && u.getPassword() == password;
        });
    
    if (it != users.end()) {
        currentUser = &(*it);
        std::cout << "Login successful! Welcome, " << currentUser->getFullName() << "!\n";
        return true;
    } else {
        std::cout << "Invalid username or password.\n";
        return false;
    }
}

void Library::logoutUser() {
    if (currentUser) {
        std::cout << "Goodbye, " << currentUser->getFullName() << "!\n";
        currentUser = nullptr;
    }
}

void Library::displayCurrentUser() {
    if (currentUser) {
        currentUser->displayInfo();
    }
}

void Library::borrowBook() {
    if (!currentUser) {
        std::cout << "Please login first.\n";
        return;
    }
    
    int bookId;
    std::cout << "\n--- Borrow Book ---\n";
    displayAvailableBooks();
    
    std::cout << "Enter book ID to borrow: ";
    std::cin >> bookId;
    
    // Find the book
    auto it = std::find_if(books.begin(), books.end(),
        [bookId](const Book& b) { return b.getId() == bookId; });
    
    if (it == books.end()) {
        std::cout << "Book not found.\n";
        return;
    }
    
    if (!it->getIsAvailable()) {
        std::cout << "Book is already borrowed.\n";
        return;
    }
    
    if (currentUser->getBorrowedCount() >= 3) {
        std::cout << "You have reached the maximum limit of 3 borrowed books.\n";
        return;
    }
    
    // Process the borrowing
    it->setIsAvailable(false);
    it->setBorrowerBy(currentUser->getUsername());
    currentUser->borrowBook(bookId);
    
    std::cout << "Book borrowed successfully!\n";
    saveBooks();
    saveUsers();
}

void Library::returnBook() {
    if (!currentUser) {
        std::cout << "Please login first.\n";
        return;
    }
    
    if (currentUser->getBorrowedCount() == 0) {
        std::cout << "You have no books to return.\n";
        return;
    }
    
    int bookId;
    std::cout << "\n--- Return Book ---\n";
    std::cout << "Your borrowed books:\n";
    for (int id : currentUser->getBorrowedBooks()) {
        auto it = std::find_if(books.begin(), books.end(),
            [id](const Book& b) { return b.getId() == id; });
        if (it != books.end()) {
            std::cout << "ID: " << id << " - " << it->getTitle() << "\n";
        }
    }
    
    std::cout << "Enter book ID to return: ";
    std::cin >> bookId;
    
    if (!currentUser->hasBorrowedBook(bookId)) {
        std::cout << "You haven't borrowed this book.\n";
        return;
    }
    
    // Process the return
    auto it = std::find_if(books.begin(), books.end(),
        [bookId](const Book& b) { return b.getId() == bookId; });
    
    if (it != books.end()) {
        it->setIsAvailable(true);
        it->setBorrowerBy("");
        currentUser->returnBook(bookId);
        
        std::cout << "Book returned successfully!\n";
        saveBooks();
        saveUsers();
    }
}

void Library::mainMenu() {
    int choice;
    
    while (true) {
        std::cout << "\n====================================\n";
        std::cout << "    LIBRARY MANAGEMENT SYSTEM\n";
        std::cout << "====================================\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Search Books\n";
        std::cout << "4. View All Books\n";
        std::cout << "5. View Available Books\n";
        std::cout << "6. Exit\n";
        std::cout << "====================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    userMenu();
                }
                break;
            case 3:
                searchBook();
                break;
            case 4:
                displayAllBooks();
                break;
            case 5:
                displayAvailableBooks();
                break;
            case 6:
                std::cout << "Thank you for using the Library Management System!\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Library::userMenu() {
    int choice;
    
    while (currentUser) {
        std::cout << "\n====================================\n";
        std::cout << "    USER MENU - " << currentUser->getFullName() << "\n";
        std::cout << "====================================\n";
        std::cout << "1. View My Profile\n";
        std::cout << "2. Search Books\n";
        std::cout << "3. View All Books\n";
        std::cout << "4. View Available Books\n";
        std::cout << "5. Borrow a Book\n";
        std::cout << "6. Return a Book\n";
        std::cout << "7. Logout\n";
        std::cout << "====================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                displayCurrentUser();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                displayAllBooks();
                break;
            case 4:
                displayAvailableBooks();
                break;
            case 5:
                borrowBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                logoutUser();
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

