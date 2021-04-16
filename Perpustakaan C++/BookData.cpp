#include "Class/BookData.h"
using namespace std;

void BookData::write(bool isBorrow, std::ostream& stream, const std::string& name) {
    time_t rawtime;
    time(&rawtime);

    tm *date = localtime(&rawtime);

    if (isBorrow) {
        stream << "~~Borrow~~"                   << std::endl
            << "Date :" << asctime(date)       << std::endl
            << "Book :" << this->bookName      << std::endl
            << "Name :" << name                << std::endl
            << std::endl;
    } else {
        stream << "~~Return~~"                    << std::endl
            << "Date :" << asctime(date)        << std::endl
            << "Book :" << this->bookName       << std::endl
            << "Name :" << name                 << std::endl
            << std::endl;
    }
}

BookData::BookData() : Book("", "", -1), Amount(-1), 
    Available(-1) {}

BookData::BookData(std::string bookName, std::string bookId, int requiredAge, 
        int Amount, int Available) :
    Book(bookName, bookId, requiredAge), Amount(Amount), 
    Available(Available) {}

void BookData::borrowBook(std::ostream& file, const std::string& memberName) {
    if (this->Available > 0) {
        this->Available--;
        write(true, file, memberName);
    } else {
        throw invalid_argument("Book is not available");
    }
}

void BookData::returnBook(std::ostream& file, const std::string& memberName) {
    if (this->Available < Amount) {
        this->Available++;
        write(false, file, memberName);
    }
}

void BookData::add(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Invalid input");
    }
    Amount += amount;
    Available += amount;
}

void BookData::remove(int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Invalid input");
    }
    if (Available >= amount) {
        Amount -= amount;
        Available -= amount;
    } else {
        throw invalid_argument("Book is not available");
    }
}

int BookData::getAmount() const {
    return Amount;
}

int BookData::getAvailable() const {
    return Available;
}
