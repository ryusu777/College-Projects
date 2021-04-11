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
            std::string Id, int age):Book(bookName, bookId, requiredAge), Name(Name), Address(Address),
        Telephone(Telephone), Id(Id), age(age) {}

    Member() : Book("", "", -1), Name(""), Address(""), Telephone(""), Id(""), age(-1) {}

    std::string getName() const{
        return Name;
    }

    std::string getAddress() const{
        return Address;
    }

    std::string getTelephone() const{
        return Telephone;
    }

    std::string getId() const{
        return Id;
    }

    int getAge() const{
        return age;
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