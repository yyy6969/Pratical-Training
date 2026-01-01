export module teacher;
import std;
import person;

using std::string;

export class Teacher:public Person
{
public:
    Teacher(string name,string age,string gender,string id);
    ~Teacher();
private:
    string m_tid;
};

Teacher::Teacher(string name,string age,string gender,string id)
:Person(name,age,gender),m_tid(id)
{
    std::print("创建老师用户\n");
}
