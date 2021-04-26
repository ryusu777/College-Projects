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

int lastKnownBookDataId;
int lastKnownMemberId;
int lastKnownEmployeeId;

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

void writeEmployee(ostream& stream, const Employee& data) {
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

Member* searchMember(const string& id) {
    for(int i=0; i<memberCount; i++){
        if(listMember[i].getId()==id && listMember[i].getBookName()!="-"){
            return &listMember[i];
        }
    }
    return nullptr;
}

bool MemberHasBook(const Member& input) {
    if (input.getBookName() != "-") {
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
    cout << "6. Add Title\n";
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

string createBookDataId() {
    //string lastId = listBook[bookCount - 1].getBookId();
    //lastId = lastId.substr(2);
    //lastKnownBookDataId = stoi(lastId);

    lastKnownBookDataId = stoi(listBook[bookCount - 1].getBookId().substr(2));

    lastKnownBookDataId++;
    stringstream stream;
    stream << "MU" << setfill('0') << setw(4) << to_string(lastKnownBookDataId);
    return stream.str();
}


string createMemberId(){
    string lastId = listMember[memberCount-1].getId();
    lastId = lastId.substr(2);
    lastKnownMemberId = stoi(lastId);
    lastKnownMemberId++;

    stringstream stream;
    stream << "M-" << setfill('0') << setw(4) << to_string(lastKnownMemberId);
    return stream.str();
}

string createIdEmployee() {
    string employeeLastId = listEmployee[employeeCount-1].getIdEmployee();
    employeeLastId = employeeLastId.substr(1);
    lastKnownEmployeeId = stoi(employeeLastId);

    lastKnownEmployeeId++;
    stringstream stream;
    stream << "E" << setfill('0') << setw(3) << to_string(lastKnownEmployeeId);
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

void borrowBook() {
    string memberId, bookName;
    Member *ptrMember = nullptr;
    BookData *ptrBookData = nullptr;

    // check member's id
    cout << "Input Member's Id: ";
    getline(cin, memberId);
    ptrMember = searchMember(memberId);
    if (ptrMember == nullptr) {
        cout << "No member found with the id of " << memberId << ".\n";
        return;
    }

    // check if member haven't return book
    if (MemberHasBook(*ptrMember) == true) {
        cout << "Member still have a book. Please return it first\n";
        return;
    }

    // check if the book's title is found
    do {
        cout << "Input Book's Name: ";
        getline(cin, bookName);
        ptrBookData = searchBook(bookName);
        if (ptrBookData != nullptr) {
            cout << "Book " << ptrBookData->getBookName() << " found.\n";
            if (ptrMember->getAge() < ptrBookData->getRequiredAge()) {
                cout << "Your age is not sufficient for this book\n";
            } else {
                // check if book is available
                ofstream historyFile;
                historyFile.open("Files/History.txt", ios::app);
                try {
                    ptrBookData->borrowBook(historyFile, ptrMember->getName());
                    ptrMember->borrowBook(ptrBookData->getBookName(), ptrBookData->getBookId(),
                            ptrBookData->getRequiredAge());
                    cout << "Book borrowed\n";
                    historyFile.close();
                    return;
                    writeData();
                } catch (const invalid_argument &err) {
                    cout << err.what() << endl;
                    historyFile.close();
                }
            }
        } else {
            cout << "No book found.\n";
        }

        string repeatStr;
        do {
            cout << "Retry input book?(y/n)\n";
            getline(cin, repeatStr);
            repeatStr = toLower(repeatStr);
        } while (repeatStr.size() != 1 ||
                (repeatStr[0] != 'y' && repeatStr[0] != 'n'));
        if (repeatStr[0] == 'y') {
            continue;
        } else {
            return;
        }
    } while (true);
}


void returnBook() {
    string memberId, bookName;
    Member *ptrMember = nullptr;
    BookData *ptrBookData = nullptr;

    // check member's id
    cout << "Input Member's Id: ";
    getline(cin, memberId);
    ptrMember = searchMember(memberId);

    if (ptrMember == nullptr) {
        cout << "No member found with the id of " << memberId << ".\n";
        return;
    }

    // check if member already return book
    if (MemberHasBook(*ptrMember) == false) {
        cout << "Member already return the book.\n";
        return;
    }

    // check if the book's title is found
    do {
        ptrBookData = searchBook(ptrMember->getBookName());
        if (ptrBookData != nullptr) {
            cout << "Book " << ptrBookData->getBookName() << " found.\n";
            ofstream historyFile;
            historyFile.open("Files/History.txt", ios::app);
            ptrBookData->returnBook(historyFile, ptrMember->getName());
            ptrMember->returnBook();
            cout << "Book returned\n";
            historyFile.close();
            writeData();
        } else {
            cout << "No book found.\n";
        }
    } while (true);
}

void showHistory(ifstream& file) {
    string input;

    while(!file.eof())
    {
        getline(file, input);
        cout << input;
    }
}

void libraryManagement();

void addTitle() {
    string bookName, bookId, requiredAge, amount, available;

    //TODO: retry input for every input
    string repeat;
    cout << "Enter book's name: ";
    getline(cin, bookName);
    bookId = createBookDataId();

    while (true) {
        cout << "Enter book's requiredAge: ";
        getline(cin, requiredAge);
        try {
            stoi(requiredAge);
            break;
        } catch (const invalid_argument& err) {
            cout << "Not an integer\n";
        }
    }

    while (true) {
        cout << "Enter book's current stock: ";
        getline(cin, amount);
        try {
            stoi(amount);
            break;
        } catch (const invalid_argument& err) {
            cout << "Not an integer\n";
        }
    }

    BookData newBook(bookName, bookId, stoi(requiredAge), stoi(amount), 
                     stoi(amount));

    bookCount++;
    ofstream bookFileOut;
    bookFileOut.open("Files/BookData.txt", ios::out);
    bookFileOut << bookCount << endl;
    for (int i = 0; i < bookCount - 1; i++) {
        writeBookData(bookFileOut, listBook[i]);
    }
    writeBookData(bookFileOut, newBook);
    bookFileOut.close();
}


void addMember() {
    string Name, Address, Telephone, Id, Age;
    string bookName{"-"}, bookId{"-"};
    int requiredAge{-1};
    cout << "Enter member's name: ";
    getline(cin, Name);

    cout << "Enter member's address: ";
    getline(cin, Address);
    
    while (true) {
        cout << "Enter member's phone number: ";
        getline(cin, Telephone);
        try {
            stoi(Telephone);
            break;
        } catch (const invalid_argument& err) {
            cout << "Not an integer\n";
        }
    }

    Id = createMemberId();

    while (true) {
        cout << "Enter member's age: ";
        getline(cin, Age);
        try {
            stoi(Age);
            break;
        } catch (const invalid_argument& err) {
            cout << "Not an integer\n";
        }
    }

    Member newMember(bookName, bookId, requiredAge, Name,
                    Address, Telephone, Id, stoi(Age));

    string repeatStr;
        do {
            cout << "Are you sure to input this data? (y/n)\n";
            getline(cin, repeatStr);
            repeatStr = toLower(repeatStr);
        } while (repeatStr.size() != 1 ||
                (repeatStr[0] != 'y' && repeatStr[0] != 'n'));
        if (repeatStr[0] == 'y') {
            memberCount++;
            ofstream memberFileOut;
            memberFileOut.open("Files/Member.txt", ios::out);
            memberFileOut << memberCount << endl;
            for (int i = 0; i < memberCount - 1; i++) {
                writeMember(memberFileOut, listMember[i]);
            }
            writeMember(memberFileOut, newMember);
            memberFileOut.close();
        } else {
            return;
        }
}

void addEmployee() {
    string nameEmployee, idEmployee, password;
    cout << "Input Employee's Name: ";
    getline(cin, nameEmployee);
    idEmployee = createIdEmployee();

    Employee newEmployee(nameEmployee, idEmployee, "");
    newEmployee.changePassword();

    cout << "Collected Data: "<< endl;
    cout << "Name: " << newEmployee.getNameEmployee() << endl;
    cout << "Id: " << newEmployee.getIdEmployee() << endl;
    string repeatStr;
        do {
            cout << "Sure to Input This Employee's Data?(y/n)\n";
            getline(cin, repeatStr);
            repeatStr = toLower(repeatStr);
        } while (repeatStr.size() != 1 ||
                (repeatStr[0] != 'y' && repeatStr[0] != 'n'));
            if (repeatStr[0] == 'y') {
                employeeCount++;
                ofstream employeeFileOut;
                employeeFileOut.open("Files/Employee.txt", ios::out);
                employeeFileOut << employeeCount << endl;
                for (int i = 0; i < employeeCount - 1; i++) {
                    writeEmployee(employeeFileOut, listEmployee[i]);
                }
                writeEmployee(employeeFileOut, newEmployee);
                employeeFileOut.close();;
        } else {
            return;
        }
}

int main() {
    gatherData();
    //login();
    int menuChosen = userChooseMenu();

    switch(menuChosen) {
        case 1:
            {
                string repeatStr;
                do {
                  borrowBook();
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
            {
            ifstream file;
            file.open("Files/History.txt", ios::in);
                showHistory(file);
            file.close();
            }
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
            libraryManagement();
            break;
        default:
            cout << "Default\n";
            break;
    }
    return 0;
}
