// Module   person
// File: person.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 14:56:48
// Description:基类人，有姓名、年龄、性别三个属性
//
export module person;
import std;
using std::string;

export class Person
{
public:
    Person(string name,int age,string gender);
    ~Person();

    string getName () const;
    int getAge () const;
    string getGender () const;
private:
    string m_name;
    int m_age;
    string m_gender;
};

Person::Person(string name,int age,string gender):m_name(name),m_age(age),m_gender(gender)
{
}

Person::~Person(){}

string Person::getName() const { return m_name; }
int Person::getAge() const { return m_age; }
string Person::getGender() const { return m_gender; }
