#include <iostream>
#include <fstream>
#include <cstdlib>
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
    return BookData(bookName, bookId, stoi(requiredAge), stoi(amount), stoi(available));
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
    return Member(bookName, bookId, stoi(requiredAge), Name,  Address, Telephone, Id, stoi(age));
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
    memberFileIn.open("Files/MemberData.txt", ios::in);
    memberFileIn >> memberCount; memberFileIn.get();
    listMember = new Member[memberCount];
    for (int i = 0; i < bookCount; i++) {
        listMember[i] = readMember(memberFileIn);
    }
    memberFileIn.close();
    //EmployeeData reading
    ifstream employeeFileIn;
    employeeFileIn.open("FIles/EmployeeData.txt", ios::in);
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

Employee* search(const string& id) {
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
        cin >> id;
        ptr = search(id);
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

BookData* searchByName(const string& bookName) {
    for (int i = 0; i < bookCount; i++) {
        if (listBook[i].getBookName() == bookName) {
            return &listBook[i];
        }
    }
    return nullptr;
}

BookData* searchById(const string& bookId) {
    for (int i = 0; i < bookCount; i++) {
        if (listBook[i].getBookId() == bookId) {
            return &listBook[i];
        }
    }
    return nullptr;
}

void stockManagement() {
    string password;
    cout << "Welcome " << currentLibrarian->getNameEmployee() << endl;
    cout << "Please insert your password: ";
    
    //TODO: add login method to Employee
    //do {
        //cin >> password;
        //if (!currentLibrarian.login(password) && password[0] != '0') {
            //cout << "Wrong Password, try again (0 to exit)\n>> ";
        //}
    //} while (!currentLibrarian.login(password) && password[0] != '0');

    currentLibrarian->changePassword();
}

int main() {
    login();
    showMenu();
    return 0;
}
