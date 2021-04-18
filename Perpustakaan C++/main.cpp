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
           << data.getRequiredAge() << endl
           << data.getAmount()      << endl
           << data.getAvailable()   << endl;
}

string toLower(string str) {
    for (unsigned i = 0; i < str.size(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
    return str;
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
           << data.getRequiredAge() << endl
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
    employeeFileOut << employeeCount << endl;
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

Member* searchMember(const string& id){
    for(int i=0; i<memberCount; i++){
        if(listMember[i].getId()==id && listMember[i].getBookName()!="-"){
            return &listMember[i];
        }
    }
    return nullptr;
}

bool MemberHasBook(const Member& input){
    if(input.getBookName()!= "-"){
        return true;
    } else {
        return false;
    }
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
    cout << "6. Exit\n";
}

int userChooseMenu() {
    showMenu();
    string inputStr;
    int input = -1, numOfMenu = 6;

    //TODO: dynamic according to number of menu
    while (input < 1 || input > numOfMenu) {
        cout << ">> ";
        getline(cin, inputStr);
        try {
            input = stoi(inputStr);
            if (input < 1 || input > numOfMenu) {
                cout << "You should enter an integer between 1 and " << numOfMenu << ".\n";
            }
        } catch (const invalid_argument& err) {
            cout << "You should enter an integer.\n";
        }
    }
    return input;
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

        cout << ">> ";
        getline(cin, inputBook);
        selectedBook = searchBook(inputBook);
        if (selectedBook == nullptr) {
            cout << "Book not found\n";
            return;
        }

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

void menu_1() {
    string memberId, bookName;
    Member *ptr1 = nullptr;
    BookData *ptr2 = nullptr;

    //check member's id
    cout << "Input Member's Id: ";
    getline(cin, memberId);
    ptr1 = searchMember(memberId);
    if (ptr1 == nullptr) {
        cout << "No member found with the id of " << memberId << ".\n";
        return;
    }

    //check if member haven't return book
    if (MemberHasBook(*ptr1)==true) {
        cout << "Member still have a book. Please return it first\n";
        return;
    }
        
    //check if the book's title is found
    do {
        cout << "Input Book's Name: ";
        getline(cin, bookName);
        ptr2 = searchBook(bookName);
        if (ptr2 != nullptr) {
            cout << "Book " << ptr2->getBookName() << " found.\n";
            if (ptr1->getAge() < ptr2->getrequiredAge()) {
                cout << "Your age is not sufficient for this book\n";
            } else {
                 //check if book is available
                ofstream historyFile;
                historyFile.open("Files/History.txt", ios::app);
                try {
                    ptr2->borrowBook (historyFile, ptr1->getName());
                    ptr1->borrowBook (ptr2->getBookName(), ptr2->getBookId(), ptr2->getrequiredAge());
                    cout << "Book borrowed\n";
                    historyFile.close();
                    return;
                    writeData();
                } catch(const invalid_argument& err){
                    cout << err.what() << endl;
                    historyFile.close();
                }    
            }            
        } else{
            cout << "No book found.\n";
        }
        
        string repeatStr;
        do {
            cout << "Retry input book?(y/n)\n";
            getline(cin, repeatStr);
            repeatStr = toLower(repeatStr);
        } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] != 'n'));
        if (repeatStr[0] == 'y') {
            continue;
        }else{
            return;
        }
    } while (true);
}

int main() {
    gatherData();
    login();
    int menuChosen = userChooseMenu();

    switch(menuChosen) {
        case 1:
            {
                string repeatStr;
                do {
                    menu_1();
                    cout << "Finished doing borrow book(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        case 2:
            cout << "Chosen 2\n";
            break;
        case 3:
            cout << "Chosen 3\n";
            break;
        case 4:
            {
                string repeatStr;
                do {
                    stockManagement();
                    cout << "Finished doing stock management(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        case 5:
            currentLibrarian->changePassword();
            break;
        case 6:
            cout << "Chosen 6\n";
            break;
        default:
            cout << "Default\n";
            break;
    }
    return 0;
}
