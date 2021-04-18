#pragma once
#include <string>
#include <fstream>

class Book{
    protected:
        std::string bookName, bookId;
        int requiredAge;

    public:

        Book(std::string bookName, std::string bookId, int requiredAge) :
            bookName(bookName), bookId(bookId), requiredAge(requiredAge) {}

        virtual void borrowBook() {}
        virtual void returnBook() {}

        void setBookName(std::string bookName);

        void setBookId(std::string bookId);

        void setRequiredAge(int requiredAge);

        std::string getBookName() const;

        std::string getBookId() const;

        int getRequiredAge() const;
};