#include "Book.h"

class BookData : Book {
private:
    int Amount, Available;
    
    void write(bool isBorrow) {
    }
public:
    BookData(std::string bookName, std::string bookId, int requiredAge, 
             int Amount, int Available) :
        Book(bookName, bookId, requiredAge), Amount(Amount), 
        Available(Available) {}

    void borrowBook() {
        Available--;
    }

    void returnBook() {
        if (Available < Amount)
            Available++;
    }
    
    void add(int amount) {
        Amount += amount;
        Available += amount;
    }

    void remove(int amount) {
        Amount -= amount;
        Available -= amount;
    }

    int getAmount() {
        return Amount;
    }

    int getAvailable() {
        return Available;
    }
};
