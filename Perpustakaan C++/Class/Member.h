#pragma once
#include "Book.h"
#include "BookData.h"
#include <string>
class Member : public Book{
    private:
    std::string Name, Address, Telephone, Id;
    int age;

    public:
    void setMember(std::string Name, std::string Address, std::string Telephone, std::string Id, int age, 
                   std::string bookName, std::string bookId, int requiredAge){
        this->Name = Name;
        this->Address = Address;
        this->Telephone = Telephone;
        this->Id = Id;
        this->age = age;
        this->bookName = bookName;
        this->bookId = bookId;
        this->requiredAge = requiredAge;
    }

    void borrowBook(std::string bookName, std::string bookId){
        this->bookName=bookName;
        this->bookId=bookId;
    }

    void returnBook(){
        bookId.clear();
        bookName.clear();
    }
};