#pragma once
#include <string>
#include <fstream>

class Book{
    protected :
        std::string bookName, bookId;
        int requiredAge;

        Book(std::string bookName, std::string bookId, int requiredAge) :
            bookName(bookName), bookId(bookId), requiredAge(requiredAge) {}

        virtual void borrowBook() {}
        virtual void returnBook() {}

        void setBookName (std::string bookName)
        {
            this->bookName=bookName;
        }

        void setBookId (std::string bookId)
        {
            this->bookId=bookId;
        }

        void setRequiredAge (int requiredAge)
        {
            this->requiredAge=requiredAge;
        }

        std::string getBookName () const {
            return bookName;
        }

        std::string getBookId () const {
            return bookId;
        }

        int getrequiredAge () const {
            return requiredAge;
        }
};
