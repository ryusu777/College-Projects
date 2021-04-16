#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <sstream>
#include "Class/BookData.h"
#include "Class/Employee.h"
#include "Class/Member.h"

using namespace std;

Employee *listEmployee;
Employee *currentLibrarian;
BookData *listBook;
Member *listMember;
int employeeCount;
int bookCount;
int memberCount;
int lastKnownId;

void writeBookData(ostream& stream, const BookData& data) {
    stream << data.getBookName()    << endl
           << data.getBookId()      << endl
           << data.getrequiredAge() << endl
           << data.getAmount()      << endl
           << data.getAvailable()   << endl;
}

BookData readBookData(istream& stream) {
    string bookName, bookId, requiredAge, amount, available;
    getline(stream, bookName);
    getline(stream, bookId);
    getline(stream, requiredAge);
    getline(stream, amount);
    getline(stream, available);
    try {
        return BookData(bookName, bookId, stoi(requiredAge), stoi(amount), stoi(available));
    } catch(const invalid_argument& err) {
        cout << "Failed to convert str to int in BookData's data\n)";
        exit(-1);
    }
}

void writeMember(ostream& stream, const Member& data) {
    stream << data.getBookName()    << endl
           << data.getBookId()      << endl
           << data.getrequiredAge() << endl
           << data.getName()        << endl
           << data.getAddress()     << endl
           << data.getTelephone()   << endl
           << data.getId()          << endl
           << data.getAge()         << endl;
}

Member readMember(istream& stream) {
    string bookName, bookId, requiredAge, Name, Address, Telephone, Id, age;
    getline(stream, bookName);
    getline(stream, bookId);
    getline(stream, requiredAge);
    getline(stream, Name);
    getline(stream, Address);
    getline(stream, Telephone);
    getline(stream, Id);
    getline(stream, age);
    try {
        return Member(bookName, bookId, stoi(requiredAge), Name,  Address, Telephone, Id, stoi(age));
    } catch(const invalid_argument& err) {
        cout << "Failed to convert str to int in Member Data\n";
        exit(-1);
    }
}

void writeEmployee(ostream& stream, const Employee& data){
    stream << data.getNameEmployee()    << endl
           << data.getIdEmployee()      << endl
           << data.getPassword()        << endl;
}

Employee readEmployee(istream& stream) {
    string nameEmployee, idEmployee, password;
    getline(stream, nameEmployee);
    getline(stream, idEmployee);
    getline(stream, password);
    return Employee(nameEmployee, idEmployee, password);
}

void gatherData() {
    //BookData reading
    ifstream bookFileIn;
    bookFileIn.open("Files/BookData.txt", ios::in);
    bookFileIn >> bookCount; bookFileIn.get();
    listBook = new BookData[bookCount];
    for (int i = 0; i < bookCount; i++) {
        listBook[i] = readBookData(bookFileIn);
    }
    bookFileIn.close();
    //MemberData reading
    ifstream memberFileIn;
    memberFileIn.open("Files/MemberData.txt");
    memberFileIn >> memberCount; memberFileIn.get();
    listMember = new Member[memberCount];
    for (int i = 0; i < memberCount; i++) {
        listMember[i] = readMember(memberFileIn);
    }
    memberFileIn.close();
    ////EmployeeData reading
    ifstream employeeFileIn;
    employeeFileIn.open("Files/EmployeeData.txt", ios::in);
    employeeFileIn >> employeeCount; employeeFileIn.get();
    listEmployee = new Employee[employeeCount];
    for (int i = 0; i < employeeCount; i++) {
        listEmployee[i] = readEmployee(employeeFileIn);
    }
    employeeFileIn.close();
}

void writeData() {
    ofstream bookFileOut;
    bookFileOut.open("Files/BookData.txt", ios::out);
    bookFileOut << bookCount << endl;
    for (int i = 0; i < bookCount; i++) {
        writeBookData(bookFileOut, listBook[i]);
    }
    bookFileOut.close();

    ofstream memberFileOut;
    memberFileOut.open("Files/MemberData.txt", ios::out);
    memberFileOut << memberCount << endl;
    for (int i= 0; i < memberCount; i++) {
        writeMember(memberFileOut, listMember[i]);
    }
    memberFileOut.close();

    ofstream employeeFileOut;
    employeeFileOut.open("Files/EmployeeData.txt", ios::out);
    employeeFileOut << employeeCount;
    for (int i = 0; i < employeeCount; i++) {
        writeEmployee(employeeFileOut, listEmployee[i]);
    }
    employeeFileOut.close();
}

Employee* searchEmployee(const string& id) {
    for (int i = 0; i < employeeCount; i++) {
        if (listEmployee[i].getIdEmployee() == id) {
            return &listEmployee[i];
        }
    }
    return nullptr;
}

void login() {
    string id;
    Employee *ptr = nullptr;

    do {
        cout << "Enter your id: ";
        getline(cin, id);
        ptr = searchEmployee(id);
        if (ptr == nullptr) {
            cout << "No employee found with the id of " << id << ".\n";
        }
    } while (ptr == nullptr);

    currentLibrarian = ptr;
}

void showMenu() {
    system("cls");
    cout << "Not Matana University Library\n";
    cout << "1. Borrow a book\n";
    cout << "2. Return a book\n";
    cout << "3. Show history\n";
    cout << "4. Stock management\n";
    cout << "5. Change password\n";
}

void changePassword(Employee& currentLibrarian) {
    currentLibrarian.changePassword();
}

string createId() {
    lastKnownId++;
    stringstream stream;
    stream << "MU" << setfill('0') << setw(4) << to_string(lastKnownId);
    return stream.str();
}

BookData* searchBook(const string& input) {
    for (int i = 0; i < bookCount; i++) {
        if (listBook[i].getBookName() == input || listBook[i].getBookId() == input) {
            return &listBook[i];
        }
    }
    return nullptr;
}

void stockManagement() {
    string password;
    cout << "Input your password(0 to exit)\n>> ";
    getline(cin, password);
    //while (!currentLibrarian->login(password) && password[0] != '0') {
        //cout << "Wrong password (0 to exit)\n>> ";
        //getline(cin, password);
    //}

    if (password[0] == '0') {
        return;
    }

    BookData* selectedBook = nullptr;
    string inputBook;

    cout << "Welcome " << currentLibrarian->getNameEmployee() << ".\n";
    cout << "Input a book's ID or Name:\n";

    do {
        cout << ">> ";
        getline(cin, inputBook);
        selectedBook = searchBook(inputBook);
        if (selectedBook == nullptr) {
            cout << "Book not found\n";
        }
    } while (selectedBook == nullptr);

    cout << selectedBook->getBookName() << " found.\n";
    cout << setw(15) << left << "Amount"    << ":" << selectedBook->getAmount()    << endl
         << setw(15) << left << "Available" << ":" << selectedBook->getAvailable() << endl;
    cout << "1. Add a book's amount\n";
    cout << "2. Remove a book's amount\n";
    
    string inputStr;
    int input = -1;

    do {
        cout << ">> ";
        getline(cin, inputStr);
        try {
            input = stoi(inputStr);
        } catch(invalid_argument err) {}
        if (input != 1 && input != 2) {
            cout << "You should enter 1 or 2\n";
        }
    } while (input != 1 && input != 2);

    switch(input) {
        case 1:
            //add book amount and available
            {
                int inputAmount = -1;
                string inputAmountStr;
                do {
                    cout << "Enter amount(0 to exit):\n>> ";
                    getline(cin, inputAmountStr);
                    try {
                        inputAmount = stoi(inputAmountStr);
                    } catch (const invalid_argument& err) {
                        cout << "You should enter an integer.\n";
                        continue;
                    }
                    try {
                        selectedBook->add(inputAmount);
                        cout << selectedBook->getBookName() << " added " 
                             << inputAmount << ".\n";
                    } catch (const invalid_argument& err) {
                        cout << err.what() << endl;
                        inputAmount = -1;
                        continue;
                    }
                } while (inputAmount < 0);
            }
            break;
        case 2:
            //remove book amount and available
            {
                int inputAmount = -1;
                string inputAmountStr;
                do {
                    cout << "Enter amount:\n>> ";
                    getline(cin, inputAmountStr);
                    try {
                        inputAmount = stoi(inputAmountStr);
                    } catch (const invalid_argument& err) {
                        cout << "You should enter an integer.\n";
                        continue;
                    }
                    try {
                        selectedBook->remove(inputAmount);
                        cout << selectedBook->getBookName() << " removed " 
                             << inputAmount << ".\n";
                    } catch (const invalid_argument& err) {
                        cout << err.what() << endl;
                        inputAmount = -1;
                        continue;
                    }

                } while (inputAmount < 0);
            }
            break;
        default:
            break;
    }
    writeData();
}

int main() {
    gatherData();
    login();
    return 0;
}
