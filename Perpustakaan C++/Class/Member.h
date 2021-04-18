#pragma once
#include "Book.h"
#include <string>
class Member : public Book{
    private:
    std::string Name, Address, Telephone, Id;
    int age;

    public:
    Member(std::string bookName, std::string bookId, int requiredAge, 
            std::string Name, std::string Address, std::string Telephone,
            std::string Id, int age);

    Member();

    std::string getName() const;

    std::string getAddress() const;

    std::string getTelephone() const;

    std::string getId() const;

    int getAge() const;

    void borrowBook(std::string bookName, std::string bookId, int requiredAge){
        this->bookName=bookName;
        this->bookId=bookId;
        this->requiredAge=requiredAge;
    }

    void returnBook(){
        bookId.clear();
        bookName.clear();
    }
};
