#include "Class/Member.h"


    Member::Member(std::string bookName, std::string bookId, int requiredAge, 
            std::string Name, std::string Address, std::string Telephone,
            std::string Id, int age): Book(bookName, bookId, requiredAge), Name(Name), Address(Address),
        Telephone(Telephone), Id(Id), age(age) {}


    Member::Member() : Book("", "", -1), Name(""), Address(""), Telephone(""), Id(""), age(-1) {}

    std::string Member::getName() const{
        return Name;
    }

    std::string Member::getAddress() const{
        return Address;
    }

    std::string Member::getTelephone() const{
        return Telephone;
    }

    std::string Member::getId() const{
        return Id;
    }

    int Member::getAge() const{
        return age;
    }

    void Member::borrowBook(std::string bookName, std::string bookId, int requiredAge){
        this->bookName=bookName;
        this->bookId=bookId;
        this->requiredAge=requiredAge;
    }

    void Member::returnBook(){
        bookId.clear();
        bookName.clear();
    }
