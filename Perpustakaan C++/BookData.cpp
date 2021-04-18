#include "Class/BookData.h"
using namespace std;

void BookData::write(bool isBorrow, ostream& stream, const string& name) {
    time_t rawtime;
    time(&rawtime);

    tm *date = localtime(&rawtime);

    if (isBorrow) {
        stream << "~~Borrow~~"                   << endl
            << "Date :" << asctime(date)       << endl
            << "Book :" << this->bookName      << endl
            << "Name :" << name                << endl
            << endl;
    } else {
        stream << "~~Return~~"                    << endl
            << "Date :" << asctime(date)        << endl
            << "Book :" << this->bookName       << endl
            << "Name :" << name                 << endl
            << endl;
    }
}

BookData::BookData() : Book("", "", -1), Amount(-1), 
    Available(-1) {}

BookData::BookData(string bookName, string bookId, int requiredAge, 
        int Amount, int Available) :
    Book(bookName, bookId, requiredAge), Amount(Amount), 
    Available(Available) {}

void BookData::borrowBook(ostream& file, const string& memberName) {
    if (this->Available > 0) {
        this->Available--;
        write(true, file, memberName);
    } else {
        throw invalid_argument("Book is not available");
    }
}

void BookData::returnBook(ostream& file, const string& memberName) {
    if (this->Available < Amount) {
        this->Available++;
        write(false, file, memberName);
    }
}

void BookData::add(int amount) {
    if (amount < 0) {
        throw invalid_argument("Invalid input");
    }
    Amount += amount;
    Available += amount;
}

void BookData::remove(int amount) {
    if (amount < 0) {
        throw invalid_argument("Invalid input");
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
