#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <sstream>
#include "Class/BookData.h"
#include "Class/Employee.h"
#include "Class/Member.h"
//TODO: Create repeat prompt and fix it
//TODO: Make program's back to main menu after finished
//TODO: Set file paths as a variable
//TODO: Stock management cls every showing book data
//TODO: Stock management login at first time only
//TODO: Input starts with >>
//TODO: Tidy up prompt
//TODO: Library management add should re-gather data
//TODO: Add option if forgot password
//TODO: Add details about each developer job.
//Probably TODO: Make history as a table

using namespace std;

Employee *listEmployee;
Employee *currentLibrarian;
BookData *listBook;
Member *listMember;
int employeeCount;
int bookCount;
int memberCount;

void write(ostream& stream, const BookData& data) {
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

void write(ostream& stream, const Member& data) {
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

void write(ostream& stream, const Employee& data) {
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

void readingBookData(ifstream& bookFileIn) {
    bookFileIn >> bookCount; bookFileIn.get();
    listBook = new BookData[bookCount];
    for (int i = 0; i < bookCount; i++) {
        listBook[i] = readBookData(bookFileIn);
    }
}

void readingEmployeeData(ifstream& employeeFileIn) {
    employeeFileIn >> employeeCount; employeeFileIn.get();
    listEmployee = new Employee[employeeCount];
    for (int i = 0; i < employeeCount; i++) {
        listEmployee[i] = readEmployee(employeeFileIn);
    }
}

void readingMember(ifstream& memberFileIn){
    memberFileIn >> memberCount; memberFileIn.get();
    listMember = new Member[memberCount];
    for (int i = 0; i < memberCount; i++) {
        listMember[i] = readMember(memberFileIn);
    }
}

void gatherData() {
    //BookData reading
    ifstream bookFileIn;
    bookFileIn.open("Files/BookData.txt", ios::in);
    readingBookData(bookFileIn);
    bookFileIn.close();

    //MemberData reading
    ifstream memberFileIn;
    memberFileIn.open("Files/Member.txt", ios::in);
    readingMember(memberFileIn);
    memberFileIn.close();

    ////EmployeeData reading
    ifstream employeeFileIn;
    employeeFileIn.open("Files/Employee.txt", ios::in);
    readingEmployeeData(employeeFileIn);
    employeeFileIn.close();
}

void writeList(ostream& output, BookData* list) {
    for (int i = 0; i < bookCount; i++) {
        write(output, list[i]);
    }
}

void writeList(ostream& output, Member* list) {
    for (int i = 0; i < memberCount; i++) {
        write(output, list[i]);
    }
}

void writeList(ostream& output, Employee* list) {
    for (int i = 0; i < employeeCount; i++) {
        write(output, listEmployee[i]);
    }
}

void writeData() {
    //TODO: Separate each read into functions
    ofstream bookFileOut;
    bookFileOut.open("Files/BookData.txt", ios::out);
    bookFileOut << bookCount << endl;
    writeList(bookFileOut, listBook);
    bookFileOut.close();

    ofstream memberFileOut;
    memberFileOut.open("Files/Member.txt", ios::out);
    memberFileOut << memberCount << endl;
    writeList(memberFileOut, listMember);
    memberFileOut.close();
  
    ofstream employeeFileOut;
    employeeFileOut.open("Files/Employee.txt", ios::out);
    employeeFileOut << employeeCount << endl;
    writeList(employeeFileOut, listEmployee);
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
        if(listMember[i].getId()==id){
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
    string id, password;
    Employee *ptr = nullptr;

    do {
        cout << "Enter your id: ";
        getline(cin, id);
        ptr = searchEmployee(id);
        if (ptr == nullptr) {
            cout << "No employee found with the id of " << id << ".\n";
        }
    } while (ptr == nullptr);

    cout << "Welcome " << ptr->getNameEmployee() << endl;
    cout << "Input your password(0 to exit)\n>> ";
    getline(cin, password);
    while (!ptr->login(password) &&
            !(password.size() == 1 && password[0] == '0')) {
        cout << "Wrong password\n>> ";
        getline(cin, password);
    }
    if (password[0] == '0')
        exit(1);
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
    cout << "6. Library Management\n";
    cout << "7. Exit\n";
}

void showBookData() {
    int nameWidth = 25, numberWidth = 5, idWidth = 10, availableWidth = 15;
    cout << left << setw(numberWidth) << "No."
        << left << setw(nameWidth) << "Title"
        << left << setw(idWidth) << "Id"
        << left << setw(availableWidth) << "Available" << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << left << setw(numberWidth) << i + 1
            << left << setw(nameWidth) << listBook[i].getBookName()
            << left << setw(idWidth) << listBook[i].getBookId()
            << left << setw(availableWidth) << to_string(listBook[i].getAvailable()) 
            + '/' + to_string(listBook[i].getAmount()) << endl;
    }
}

int userChooseMenu(int numOfMenu) {
    string inputStr;
    int input = -1;

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
    int lastKnownBookDataId;
    try {
        lastKnownBookDataId = stoi(listBook[bookCount - 1].getBookId().substr(2));
    } catch (const invalid_argument& err) {
        cout << "Error converting BookData Id into integer\n";
        exit(-1);
    }

    lastKnownBookDataId++;
    stringstream stream;
    stream << "MU" << setfill('0') << setw(4) << to_string(lastKnownBookDataId);
    return stream.str();
}

string createMemberId(){
    string lastId = listMember[memberCount-1].getId();
    int lastKnownMemberId;
    lastId = lastId.substr(2);
    try {
        lastKnownMemberId = stoi(lastId);
    } catch (const invalid_argument& err) {
        cout << "Error converting Member Id into integer\n";
        exit(-1);
    }
    lastKnownMemberId++;

    stringstream stream;
    stream << "M-" << setfill('0') << setw(4) << to_string(lastKnownMemberId);
    return stream.str();
}

string createIdEmployee() {
    string employeeLastId = listEmployee[employeeCount-1].getIdEmployee();
    employeeLastId = employeeLastId.substr(1);
    int lastKnownEmployeeId;
    try {
        lastKnownEmployeeId = stoi(employeeLastId);
    } catch (const invalid_argument& err) {
        cout << "Error converting Employee Id into integer\n";
        exit(-1);
    }

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
    cout << "Input your password\n>> ";
    getline(cin, password);
    while (!currentLibrarian->login(password) &&
            !(password.size() == 1 && password[0] == '0')) {
        cout << "Wrong password\n>> ";
        getline(cin, password);
    }

    if (password[0] == '0') {
        return;
    }

    BookData* selectedBook = nullptr;
    string inputBook;

    cout << "Welcome " << currentLibrarian->getNameEmployee() << ".\n";
    showBookData();
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
                    writeData();
                    return;
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
}

void showHistory(ifstream& file) {
    string input;

    while(!file.eof())
    {
        getline(file, input);
        cout << input << endl;
    }
}

void addTitle() {
    string bookName, bookId, requiredAge, amount, available;

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

    int width = 18;
    cout << "\nData collected:\n";
    cout << left << setw(width) << "Name"            << ": " << newBook.getBookName() << endl;
    cout << left << setw(width) << "Id"              << ": " << newBook.getBookId() << endl;
    cout << left << setw(width) << "Required Age"    << ": " << newBook.getRequiredAge() << endl;
    cout << left << setw(width) << "Stock Amount"    << ": " << newBook.getAmount() << endl;
    cout << left << setw(width) << "Stock Available" << ": " << newBook.getAvailable() << endl;
    cout << endl;

    string confirmationStr;
    do {
        cout << "Sure to add this book?(y/n)\n";
        getline(cin, confirmationStr);
        confirmationStr = toLower(confirmationStr);
    } while (confirmationStr.size() != 1 ||
            (confirmationStr[0] != 'y' && confirmationStr[0] != 'n'));
    if (confirmationStr[0] == 'y') {
        bookCount++;
        ofstream bookFileOut;
        bookFileOut.open("Files/BookData.txt", ios::out);
        bookFileOut << bookCount << endl;
        for (int i = 0; i < bookCount - 1; i++) {
            write(bookFileOut, listBook[i]);
        }
        write(bookFileOut, newBook);
        bookFileOut.close();

    } else {
        return;
    }
}

void removeTitle() {
    cout << "Welcome\n";
    showBookData();

    string inputStr;
    int index;

    //choose title's index
    while (true) {
        cout << "Input title's no. to be removed(0 to exit)\n>> ";
        getline(cin, inputStr);
        try {
            index = stoi(inputStr);
            if (index < 1 || index > bookCount) {
                if (index == 0) {
                    return;
                }
                cout << "No index found\n";
                continue;
            }
            index--;
            break;
        } catch (const invalid_argument& err) {
            cout << "You should enter an integer\n";
        }
    }

    //confimation
    int width = 20;
    cout << "Book selected:\n";
    cout << setw(width) << "Name"           << ": " << listBook[index].getBookName() << endl;
    cout << setw(width) << "Id"             << ": " << listBook[index].getBookId() << endl;
    cout << setw(width) << "Required Age"   << ": " << to_string(listBook[index].getRequiredAge()) + " years old"<< endl;
    if (listBook[index].getAvailable() < listBook[index].getAmount()) {
        cout << "Not all book is available, removing isn't allowed\n";
        return;
    }

    cout << "Confirm delete?\n>> ";
    string confirmationStr;
    do {
        cout << "Sure to remove this book?(y/n)\n";
        getline(cin, confirmationStr);
        confirmationStr = toLower(confirmationStr);
    } while (confirmationStr.size() != 1 ||
            (confirmationStr[0] != 'y' && confirmationStr[0] != 'n'));
    if (confirmationStr[0] == 'y') {
        bookCount--;
        ofstream bookFileOut;
        bookFileOut.open("Files/BookData.txt", ios::out);
        bookFileOut << bookCount << endl;
        for (int i = 0; i < bookCount + 1; i++) {
            if (i != index) {
                write(bookFileOut, listBook[i]);
            }
        }
        bookFileOut.close();
    } else {
        return;
    }

    //Delete listBook and re read it
    delete[] listBook;
    ifstream bookFileIn;
    bookFileIn.open("Files/BookData.txt");
    readingBookData(bookFileIn);
    bookFileIn.close();
}

void addMember() {
    string Name, Address, Telephone, Id, Age;
    string bookName{"-"}, bookId{"-"};
    int requiredAge{-1};
    cout << "Enter member's name: ";
    getline(cin, Name);

    cout << "Enter member's address: ";
    getline(cin, Address);

    cout << "Enter member's phone number: ";
    getline(cin, Telephone);

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

    //Vero TODO: Show member's data
    cout << "Name\t\t: " << Name << endl << "Address\t\t: " << Address << endl <<
            "Telephone\t: " << Telephone << endl << " Member Id\t: " << Id << endl <<
            "Age\t\t: " << Age << endl;

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
            write(memberFileOut, listMember[i]);
        }
        write(memberFileOut, newMember);
        memberFileOut.close();
    } else {
        return;
    }

    //Delete list member and re read it
    delete[] listMember;
    ifstream memberFileIn;
    memberFileIn.open("Files/Member.txt");
    readingMember(memberFileIn);
    memberFileIn.close();
}

void removeMember(){
    cout << "Welcome\n";
    int memberNameWidth = 20, numberWidth = 5, memberIdWidth = 10, memberAddressWidth = 30, memberTelpWidth= 15, memberAgeWidth = 5;
    cout << left << setw(numberWidth) << "No."
        << left << setw(memberNameWidth) << "Name"
        << left << setw(memberIdWidth) << "Member Id"
        << left << setw(memberAddressWidth) << "Address"
        << left << setw(memberTelpWidth) << "Telp"
        << left << setw(memberAgeWidth) << "Age" << endl;
    for (int i = 0; i < memberCount; i++) {
        cout << left << setw(numberWidth) << i + 1
            << left << setw(memberNameWidth) << listMember[i].getName()
            << left << setw(memberIdWidth) << listMember[i].getId()
            << left << setw(memberAddressWidth) << listMember[i].getAddress()
            << left << setw(memberTelpWidth) << listMember[i].getTelephone()
            << left << setw(memberAgeWidth) << to_string(listMember[i].getAge())  << endl;
    }
    string inputStr;
    int index;

    //choose member's index
    //Vero TODO: Add option to exit removeMember
    while (true) {
        cout << "Input member's no. to be removed (input 0 to exit): \n>> ";
        getline(cin, inputStr);
        try {
            index = stoi(inputStr);
            if (index < 1 || index > memberCount) {
                cout << "Wrong integer\n";
                continue;
            }
            index--;
            break;
        } catch (const invalid_argument& err) {
            cout << "You should enter an integer\n";
        }
    }

    //confimation
    int width = 20;
    cout << "Member selected:\n";
    cout << setw(width) << "Name"       << ": " << listMember[index].getName() << endl;
    cout << setw(width) << "Id"         << ": " << listMember[index].getId() << endl;
    cout << setw(width) << "Address"    << ": " << listMember[index].getAddress() << endl;
    cout << setw(width) << "Telephone"  << ": " << listMember[index].getTelephone() << endl;
    cout << setw(width) << "Age"        << ": " << to_string(listMember[index].getAge()) + " years old"<< endl;
    if (listMember[index].getBookName() != "-") {
        cout << "Member hasn't returned book, removing isn't allowed\n";
        return;
    }

    cout << "Confirm delete?\n>> ";
    string confirmationStr;
    do {
        cout << "Sure to remove this member?(y/n)\n";
        getline(cin, confirmationStr);
        confirmationStr = toLower(confirmationStr);
    } while (confirmationStr.size() != 1 ||
            (confirmationStr[0] != 'y' && confirmationStr[0] != 'n'));
    if (confirmationStr[0] == 'y') {
        memberCount--;
        ofstream memberFileOut;
        memberFileOut.open("Files/Member.txt", ios::out);
        memberFileOut << memberCount << endl;
        for (int i = 0; i < memberCount + 1; i++) {
            if (i != index) {
                write(memberFileOut, listMember[i]);
            }
        }
        memberFileOut.close();
    } else {
        return;
    }

    //Delete list member and re read it
    delete[] listMember;
    ifstream memberFileIn;
    memberFileIn.open("Files/Member.txt");
    readingMember(memberFileIn);
    memberFileIn.close();
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
            write(employeeFileOut, listEmployee[i]);
        }
        write(employeeFileOut, newEmployee);
        employeeFileOut.close();;
    } else {
        return;
    }

    //Delete listEmployee and re read it
    delete[] listEmployee;
    ifstream employeeFileIn;
    employeeFileIn.open("Files/Employee.txt");
    readingEmployeeData(employeeFileIn);
    employeeFileIn.close();
}

void removeEmployee() {
    cout << "Welcome\n";
    int nameWidth = 25, numberWidth = 5, idWidth = 10, availableWidth = 15;
    cout << left << setw(numberWidth) << "No."
         << left << setw(nameWidth) << "Name"
         << left << setw(idWidth) << "Id" << endl;
    for (int i = 0; i < employeeCount; i++) {
        cout << left << setw(numberWidth) << i + 1
             << left << setw(nameWidth) << listEmployee[i].getNameEmployee()
             << left << setw(idWidth) << listEmployee[i].getIdEmployee() << endl;
    }

    string inputStr;
    int index;

    //choose Employee's index
    //Sab TODO: Option to exit removeEmployee
    while (true) {
        cout << "Input Employee's no. to be removed (input 0 to exit\n>> ";
        getline(cin, inputStr);
        try {
            index = stoi(inputStr);
            if (index < 1 || index > employeeCount) {
                if (index == 0) {
                    return;
                }
                else {
                    cout << "Wrong integer\n";
                    continue;
                }
            }
            index--;
            break;
        } catch (const invalid_argument& err) {
            cout << "You should enter an integer\n";
        }
    }

    //confimation
    int width = 20;
    cout << "Employee selected:\n";
    cout << setw(width) << "Name"           << ": " << listEmployee[index].getNameEmployee() << endl;
    cout << setw(width) << "Id"             << ": " << listEmployee[index].getIdEmployee() << endl;
    
    cout << "Confirm delete?\n>> ";
    string confirmationStr;
    do {
        cout << "Sure to remove this employee?(y/n)\n";
        getline(cin, confirmationStr);
        confirmationStr = toLower(confirmationStr);
    } while (confirmationStr.size() != 1 ||
            (confirmationStr[0] != 'y' && confirmationStr[0] != 'n'));
    if (confirmationStr[0] == 'y') {
        employeeCount--;
        ofstream employeeFileOut;
        employeeFileOut.open("Files/Employee.txt", ios::out);
        employeeFileOut << employeeCount << endl;
        for (int i = 0; i < employeeCount + 1; i++) {
            if (i != index) {
                write(employeeFileOut, listEmployee[i]);
            }
        }
        employeeFileOut.close();
    } else {
        return;
    }

    //Delete listEmployee and re read it
    delete[] listEmployee;
    ifstream employeeFileIn;
    employeeFileIn.open("Files/Employee.txt");
    readingEmployeeData(employeeFileIn);
    employeeFileIn.close();
}

void libraryManagement() {
    string password;
    cout << "Input your password\n>> ";
    getline(cin, password);
    while (!currentLibrarian->login(password) &&
            !(password.size() == 1 && password[0] == '0')) {
        cout << "Wrong password(0 to exit)\n>> ";
        getline(cin, password);
    }

    if (password[0] == '0') {
        return;
    }

    cout << "Welcome to library management.\n";
    cout << "1. Add title.\n"
         << "2. Remove title.\n"
         << "3. Add Member.\n"
         << "4. Remove Member.\n"
         << "5. Add Employee.\n"
         << "6. Remove Employee.\n"
         << "7. Exit.\n";
    int chosen = userChooseMenu(7);
    switch (chosen) {
        case 1:
            {
                string repeatStr;
                do {
                    addTitle();
                    cout << "Finished adding title(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        case 2:
            {
                string repeatStr;
                do {
                    removeTitle();
                    cout << "Finished removing title(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        case 3:
            {
                string repeatStr;
                do {
                    addMember();
                    cout << "Finished adding member(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        case 4:
            {
                string repeatStr;
                do {
                    removeMember();
                    cout << "Finished removing member(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        case 5:
            {
                string repeatStr;
                do {
                    addEmployee();
                    cout << "Finished adding employee(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        case 6:
            {
                string repeatStr;
                do {
                    removeEmployee();
                    cout << "Finished removing employee(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
            break;
        default:
            break;
    }
}

int main() {
    gatherData();
    login();
    showMenu();
    int menuChosen = userChooseMenu(7);

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
            {
                string repeatStr;
                do {
                    returnBook();
                    cout << "Finished doing return book(y/n)?\n>> ";
                    getline(cin, repeatStr);
                    repeatStr = toLower(repeatStr);
                } while (repeatStr.size() != 1 || (repeatStr[0] != 'y' && repeatStr[0] == 'n'));
            }
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
            {
                currentLibrarian->changePassword();
                ofstream employeeFile;
                employeeFile.open("Files/Employee.txt", ios::out);
                employeeFile << employeeCount << endl;
                writeList(employeeFile, listEmployee);
                employeeFile.close();
            }
            break;
        case 6:
            //TODO create repetition
            libraryManagement();
            break;
        default:
            cout << "Program finished\n";
            break;
    }
    return 0;
}