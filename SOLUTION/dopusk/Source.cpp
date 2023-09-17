#include <iostream>
#include <string>

using namespace std;

class Human 
{
    int age{};
    int weight{};
    string fio{};

public:
    virtual int getAge() = 0;
};

class Student : public Human 
{
    double averageMark{};
    int age{};
    int height{};
    string fio{};
public:
    Student() 
    {
        this->age = 0;
        this->fio = "";
        this->height = 0;
    }
    Student(int age, int height, string name)
    {
        this->age = age;
        this->fio = name;
        this->height = height;
    }
    Student(const Student& obj) 
    {
        this->fio = obj.fio;
        this->age = obj.age;
        this->height = height;
    }
    ~Student() 
    {
        fio.clear();
    }
    int getAge() 
    {
        cout << "Student's age: " << age;
    }
};

class Employee :public Human 
{
    int age, height;
    double hoursRate{};
    string department{};
public:
    Employee() {
        this->age = 0;
        this->height = 0;
        this->hoursRate = 0;
        this->department = "";
    }
    Employee(int age, int height, double hoursRate, string department) 
    {
        this->age = age;
        this->height = height;
        this->hoursRate = hoursRate;
        this->department = department;

    }
    Employee(const Employee& obj) {
        this->age = obj.age;
        this->height = obj.height;
        this->hoursRate = obj.hoursRate;
        this->department = obj.department;
    }
    ~Employee() 
    {
        department.clear();
    }
    int getAge() 
    {
        cout << "Employee's's age: " << age;
    }
};

int main() {
    Student first(18, 160, "Ivanov Ivan Ivanovich");
    Student second(19, 170, "Petrov Petr Petrovich");
   

    Employee one(25, 180, 7.2, "IT");
    Employee two(30, 190, 6.3, "Marketing");
   

        return 0;
}
