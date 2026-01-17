// Module teacher
// File: teacher.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 14:54:38
// Description:老师类，老师进行对课程的授课，其实相当于学生的选课
//
export module teacher;
import std;
import person;

using std::string; using std::shared_ptr;
using std::vector;

export class Teacher:public Person
{
public:
    Teacher(string name,int age,string gender,string id);
    string getTeacherId() const;
    void addCourse();
    ~Teacher();
private:
    string m_tid;//老师id
    vector<std::shared_ptr<class Course>> m_arranged_courses;//所教的课程
};

Teacher::Teacher(string name,int age,string gender,string id)
:Person(name,age,gender),m_tid(id)
{
    std::print("创建老师用户\n");
}

string Teacher::getTeacherId() const
{
    return m_tid;
}

void Teacher::addCourse()
{
    m_arranged_courses.pushback(shared_ptr<Class> cla);
}
