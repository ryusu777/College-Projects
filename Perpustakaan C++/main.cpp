#include <iostream>
#include <cstdlib>
using namespace std;

void showMenu() {
    system("clear");
    cout << "Not Matana University Library\n";
    cout << "1. Borrow a book\n";
    cout << "2. Return a book\n";
    cout << "3. Show history\n";
    cout << "4. Stock management\n";
    cout << "5. Change password\n";
}

int main() {
    showMenu();
    return 0;
}
