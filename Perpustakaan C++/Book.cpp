#include "Class/Book.h"

Book::Book(std::string bookName, std::string bookId, int requiredAge) :
    bookName(bookName), bookId(bookId), requiredAge(requiredAge) {}

void Book::setBookName(std::string bookName)
{
    this->bookName=bookName;
}

void Book::setBookId(std::string bookId)
{
    this->bookId=bookId;
}

void Book::setRequiredAge(int requiredAge)
{
    this->requiredAge=requiredAge;
}

std::string Book::getBookName() const {
    return bookName;
}

std::string Book::getBookId() const {
    return bookId;
}

int Book::getRequiredAge() const {
    return requiredAge;
}