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

void gatherData() {
    ifstream employeeFile;
    //TODO: Open employeeFile

    employeeFile >> employeeCount;

    listEmployee = new Employee[employeeCount];

    for (int i = 0; i < employeeCount; i++) {
        string nameEmployee, idEmployee, password, day;
        getline(employeeFile, nameEmployee);
        employeeFile.get();
        employeeFile >> idEmployee >> password >> day;
        listEmployee[i] = Employee(nameEmployee, idEmployee, password, day);
    }
    employeeFile.close();
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
    Employee currentLibrarian;
    login();
    showMenu();
    return 0;
}
