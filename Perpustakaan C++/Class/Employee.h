#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

class Employee{
    public:
        Employee() : nameEmployee(""), idEmployee(""), password("") {}
        Employee(std::string nameEmployee, std::string idEmployee, std::string password) :
        nameEmployee(nameEmployee), idEmployee(idEmployee), password(password) {}

        void setNameEmployee (std::string nameEmployee);

        void setIdEmployee (std::string idEmployee);

        void changePassword();

        std::string getNameEmployee() const;
        
        std::string getIdEmployee() const;
        
        std::string getPassword() const;
        
        bool login(std::string inputPassword) const;

    private:
        std::string nameEmployee, idEmployee, password;
};