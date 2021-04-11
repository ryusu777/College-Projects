#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

class Employee{
    public:
        Employee() : nameEmployee(""), idEmployee(""), password("") {}
        Employee(std::string nameEmployee, std::string idEmployee, std::string password) : nameEmployee(nameEmployee), idEmployee(idEmployee), password(password) {}

        void setNameEmployee (std::string nameEmployee){
            this->nameEmployee=nameEmployee;
        }

        void setIdEmployee (std::string idEmployee){
            this->idEmployee=idEmployee;
        }

        void changePassword() {
            std::string oldPassword;
            do {
                std::cout << "Input Current Password" << std::endl;
                std::cin >> oldPassword;
                if(oldPassword != this->password) {
                    std::cout << "Wrong Password\n";
                }
            } while (oldPassword != this->password);

            std::string newPassword, passwordConfirm;

            do {
                std::cout << "Input New Password" << std::endl;
                std::cin >> newPassword;
                system("cls");
                std::cout << "Confirm New Password" << std::endl;
                std::cin >> passwordConfirm;
                if (newPassword != passwordConfirm) {
                    std::cout << "Wrong Password\n";
                }
            } while (newPassword != passwordConfirm);
        }

        std::string getNameEmployee() const {
            return nameEmployee;
        }
        
        std::string getIdEmployee() const {
            return idEmployee;
        }
        
        std::string getPassword() const {
            return password;
        }
        
    private:
        std::string nameEmployee, idEmployee, password;
};