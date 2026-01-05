export module student;
import std;
import person;

using std::string; using std::vector;

export class Student : public Person
{
public:
    Student(string name,int age,string gender,string id);
    void choseClass
private:
    string m_sid;
    double final_grade;
    double midian;
    vector<double> hm_grade;
};

Student::Student(string name,int age,string gender,string id)
:Person(name,age,gender),m_sid(id)
{
    std::print("创建学生用户\n");
}
