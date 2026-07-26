#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;
    std::string borrowerBy;

public:
    // Constructor
    Book();
    Book(int id, std::string title, std::string author, std:: string isbn);

    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getIsbn() const;
    bool getIsAvailable() const;
    std::string getBorrowerBy() const;

    //setters
    void setId(int id);
    void setTitle(std::string title);
    void setAuthor(std::string author);
    void setIsbn(std::string isbn);
    void setIsAvailable(bool status);
    void setBorrowerBy(std::string username);

    //Display
    void displayInfo() const;

    //File operations
    std::string toString() const;
    static Book fromString(const std::string& str);

};

#endif
