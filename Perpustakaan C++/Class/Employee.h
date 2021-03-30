#pragma once
#include <string>

class Employee{
    public:
        void setNameEmployee (std::string nameEmployee){
            this->nameEmployee=nameEmployee;
        }

        void setIdEmployee (std::string idEmployee){
            this->idEmployee=idEmployee;
        }

        void setPassword (std::string password){
            this->password=password;
        }

        void setDay (std::string day) {
            this-> day=day;
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
        
        std::string getDay() const {
            return day;
        }
    private:
        std::string nameEmployee, idEmployee, password, day;
};
