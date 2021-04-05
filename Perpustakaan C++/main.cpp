#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Class/BookData.h"
#include "Class/Employee.h"
using namespace std;

Employee *listEmployee;
int employeeCount;

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

void login(Employee& currentLibrarian) {
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

    currentLibrarian = *ptr;
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

int main() {

    Employee currentLibrarian;
    login(currentLibrarian);
    showMenu();
    return 0;
}
