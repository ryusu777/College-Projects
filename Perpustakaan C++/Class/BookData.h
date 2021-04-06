#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "Book.h"

class BookData : public Book {
private:
    int Amount, Available;
    
    void write(bool isBorrow, std::ofstream& file, const std::string& name) {
        time_t rawtime;
        time(&rawtime);

        tm *date = localtime(&rawtime);

        if (isBorrow) {
            file << "~~Borrow~~"                   << std::endl
                << "Date :" << asctime(date)       << std::endl
                << "Book :" << this->bookName      << std::endl
                << "Name :" << name                << std::endl
                << std::endl;
        } else {
            file << "~~Return~~"                    << std::endl
                << "Date :" << asctime(date)        << std::endl
                << "Book :" << this->bookName       << std::endl
                << "Name :" << name                 << std::endl
                << std::endl;
        }
    }
public:
    BookData(std::string bookName, std::string bookId, int requiredAge, 
            int Amount, int Available) :
        Book(bookName, bookId, requiredAge), Amount(Amount), 
        Available(Available) {}

    void borrowBook(std::ofstream& file, const std::string& memberName) {
        if (this->Available > 0) {
            this->Available--;
            write(true, file, memberName);
        } 
    }

    void returnBook(std::ofstream& file, const std::string& memberName) {
        if (this->Available < Amount) {
            this->Available++;
            write(false, file, memberName);
        }
    }
    
    void add(int amount) {
        Amount += amount;
        Available += amount;
    }

    void remove(int amount) {
        if (Available >= amount) {
            Amount -= amount;
            Available -= amount;
        } else {
            std::cout << "Cannot remove non-available books!\n";
        }
    }

    int getAmount() {
        return Amount;
    }

    int getAvailable() {
        return Available;
    }
};
