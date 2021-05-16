#include "../Class/Employee.h"

Employee::Employee(std::string nameEmployee, std::string idEmployee, 
        std::string password) : 
    nameEmployee(nameEmployee), idEmployee(idEmployee), password(password) {}

Employee::Employee() : nameEmployee(""), idEmployee(""), password("") {}

void Employee::changePassword() {
    if (this->password.size() != 0) {
        std::string oldPassword;
        do {
            std::cout << "Input Current Password(0 to exit)" << std::endl 
                << ">> ";
            std::getline(std::cin, oldPassword);
            if (oldPassword.size() == 1 && oldPassword[0] == '0')
                return;
            if (oldPassword != this->password)
                std::cout << "Wrong Password\n";
        } while (oldPassword != this->password);
    }

    std::string newPassword, passwordConfirm;

    do {
        std::cout << "Input New Password" << std::endl << ">> ";
        std::getline(std::cin, newPassword);
        system("cls");
        std::cout << "Confirm New Password(0 to cancel and exit)" << std::endl 
            << ">> ";
        std::getline(std::cin, passwordConfirm);
        if (passwordConfirm.size() == 1 && passwordConfirm[0] == '0')
            return;
        if (newPassword != passwordConfirm)
            std::cout << "Wrong Password\n";
    } while (newPassword != passwordConfirm);

    this->password = newPassword;
}

std::string Employee::getNameEmployee() const {
    return nameEmployee;
}

std::string Employee::getIdEmployee() const {
    return idEmployee;
}

std::string Employee::getPassword() const {
    return password;
}

bool Employee::login(std::string inputPassword) const {
    if (inputPassword == password)
        return true;
    else
        return false;
}
