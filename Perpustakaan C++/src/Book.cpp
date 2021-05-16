#include "../Class/Book.h"
#include <fstream>
#include <string>

Book::Book(std::string bookName, std::string bookId, int requiredAge) :
    bookName(bookName), bookId(bookId), requiredAge(requiredAge) {}

std::string Book::getBookName() const {
    return bookName;
}

std::string Book::getBookId() const {
    return bookId;
}

int Book::getRequiredAge() const {
    return requiredAge;
}
