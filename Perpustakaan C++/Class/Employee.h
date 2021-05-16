#pragma once
#include <string>

class Employee{
public:
    //Default Constructor
    Employee();

    //Constructor
    Employee(std::string nameEmployee, std::string idEmployee, std::string password);

    //Function to change password that need old password
    void changePassword();

    //Getter for nameEmployee
    std::string getNameEmployee() const;
    
    //Getter for idEmployee
    std::string getIdEmployee() const;

    //Getter for password
    std::string getPassword() const;
    
    //Return true if inputPassword is equal to password, false otherwise
    bool login(std::string inputPassword) const;

private:
    std::string nameEmployee, idEmployee, password;
};
