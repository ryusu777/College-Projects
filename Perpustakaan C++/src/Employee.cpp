#include "../Class/Employee.h"

Employee::Employee(std::string nameEmployee, std::string idEmployee, 
                   std::string password) : 
        nameEmployee(nameEmployee), idEmployee(idEmployee), 
        password(password) {}

Employee::Employee() : nameEmployee(""), idEmployee(""), password("") {}
void Employee::setNameEmployee (std::string nameEmployee)
{
    this->nameEmployee=nameEmployee;
}

void Employee::setIdEmployee (std::string idEmployee)
{
    this->idEmployee=idEmployee;
}

void Employee::changePassword()
{
    if (this->password.size() != 0) {
        std::string oldPassword;
        do {
            std::cout << "Input Current Password" << std::endl;
            std::getline(std::cin, oldPassword);
            if(oldPassword != this->password) {
                std::cout << "Wrong Password\n";
            }
        } while (oldPassword != this->password);
    }
    
        std::string newPassword, passwordConfirm;

        do {
            std::cout << "Input New Password" << std::endl;
            std::getline(std::cin, newPassword);
            system("cls");
            std::cout << "Confirm New Password" << std::endl;
            std::getline(std::cin, passwordConfirm);
            if (newPassword != passwordConfirm) {
                std::cout << "Wrong Password\n";
            }
        } while (newPassword != passwordConfirm);
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
        
bool Employee::login(std::string inputPassword) const{
    if (inputPassword==password)
    {
        return true;
    }
    else
    {
        return false;
    }
}
