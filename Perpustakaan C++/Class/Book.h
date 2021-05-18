#pragma once
#include <string>

class Book{
protected:
    std::string bookName, bookId;
    int requiredAge;

public:
    //Constructor
    Book(std::string bookName, std::string bookId, int requiredAge);

    //Function to borrow book
    virtual void borrowBook() {}
    //Function to return book
    virtual void returnBook() {}

    std::string getBookName() const;

    std::string getBookId() const;

    int getRequiredAge() const;
};
