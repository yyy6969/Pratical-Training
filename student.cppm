export module student;
import std;
import person;

using std::string;

export class Student : public Person
{
public:
    Student(string name,string age,string gender,string id);
private:
    string m_sid;
};

Student::Student(string name,string age,string gender,string id)
:Person(name,age,gender),m_sid(id)
{}
