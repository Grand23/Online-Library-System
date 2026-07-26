#include "Book.h"
#include <sstream>
#include <iomanip>

Book::Book() : id(0), title(""), author(""),
isbn(""), isAvailable(true), borrowerBy("") {}

Book::Book(int id, std::string title, std::string author, std:: string isbn)
    : id(id), title(title), author(author), isbn(isbn), isAvailable(true), borrowerBy("") {}

// Getters
int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getIsbn() const { return isbn; }
bool Book::getIsAvailable() const { return isAvailable; }
std::string Book::getBorrowerBy() const { return borrowerBy; }

// Setters
void Book::setId(int id) { this->id = id; }
void Book::setTitle(std::string title) { this->title = title; }
void Book::setAuthor(std::string author) { this->author = author; }
void Book::setIsbn(std::string isbn) { this->isbn = isbn; }
void Book::setIsAvailable(bool status) { this->isAvailable = status; }
void Book::setBorrowerBy(std::string username) { this->borrowerBy = username; }

void Book::displayInfo() const {
    std::cout << "\n--- Book Information ---\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    std::cout << "Status: " << (isAvailable ? "Available" : "Borrowed") << "\n";
    if (!isAvailable) {
        std::cout << "Borrowed By: " << borrowerBy << "\n";
    }
    std::cout << "------------------------\n";
}

std::string Book::toString() const {
    std::ostringstream oss;
    oss << id << "|" << title << "|" << author << "|" << isbn << "|" << (isAvailable ? "1" : "0") << "|" << borrowerBy;
    return oss.str();
}

Book Book::fromString(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    Book book;

    std::getline(iss, token, '|');
    if (!token.empty()) book.id = std::stoi(token);

    std::getline(iss, token, '|');
    book.title = token;

    std::getline(iss, token, '|');
    book.author = token;

    std::getline(iss, token, '|');
    book.isbn = token;

    std::getline(iss, token, '|');
    book.isAvailable = (token == "1");

    std::getline(iss, token, '|');
    book.borrowerBy = token;

    return book;
}

