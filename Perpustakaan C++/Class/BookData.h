#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "Book.h"

class BookData : public Book {
private:
    int Amount, Available;
    
    //Function that takes true to write to the ostream to output borrowing 
    //history and takes false to output return history. Takes the member's name 
    //as a string
    void write(bool isBorrow, std::ostream& stream, const std::string& name);
public:
    //Default constructor
    BookData();    

    //Constructor
    BookData(std::string bookName, std::string bookId, int requiredAge, 
            int Amount, int Available);

    //Borrow book and write to history, takes an ostream and a string
    void borrowBook(std::ostream& file, const std::string& memberName);

    //Return book and write to history, takes an ostream and a string
    void returnBook(std::ostream& file, const std::string& memberName);
    
    //Add the amount of books
    void add(int amount);

    //Remove the amount of books if the book is available
    void remove(int amount);

    //Getter for amount
    int getAmount() const;

    //Getter for available
    int getAvailable() const;
};