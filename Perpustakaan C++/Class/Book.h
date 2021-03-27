#include <string>

class Book{
    public :
        Book(std::string bookName, std::string bookId, int requiredAge) :
            bookName(bookName), bookId(bookId), requiredAge(requiredAge) {}

        virtual void borrowBook ();

        virtual void returnBook();

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

    protected:
        std::string bookName, bookId;
        int requiredAge;
};
