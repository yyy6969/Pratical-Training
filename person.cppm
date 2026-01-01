export module person;
import std;

using std::string;

export class Person
{
public:
    Person(string name,string age,string gender);
    ~Person();
private:
    string m_name;
    string m_age;
    string m_gender;
};

Person::Person(string name,string age,string gender):m_name(name),m_age(age),m_gender(gender)
{
    std::print("创建学生用户\n");
}

Person::~Person(){}
