#pragma once
#include "Book.h"
#include <string>

class Member : public Book {
private:
    std::string Name, Address, Telephone, Id;
    int age;

public:
    //Constructor
    Member(std::string bookName, std::string bookId, int requiredAge, 
            std::string Name, std::string Address, std::string Telephone,
            std::string Id, int age);

    //Default constructor
    Member();

    //Getter for Name
    std::string getName() const;

    //Getter for Address
    std::string getAddress() const;

    //Getter for Telephone
    std::string getTelephone() const;

    //Getter for Id
    std::string getId() const;

    //Getter for age
    int getAge() const;

    //Function for setting book data
    void borrowBook(std::string bookName, std::string bookId, int requiredAge);

    //Function for clearing book data
    void returnBook();
};
