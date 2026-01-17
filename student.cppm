// Module   student
// File: student.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 14:55:54
// Description:学生类，进行选课操作
//
export module student;
import std;
import person;
import Class;


using std::string; using std::vector;
using std::shared_ptr;

export class Student : public Person
{
public:
    Student(string name,int age,string gender,string id);
    string getStudentId() const;
    void addCourse(Class cla);
private:
    string m_sid;
    vector<std::shared_ptr<class Course>> m_selected_courses;//所选的课程
};

Student::Student(string name,int age,string gender,string id)
:Person(name,age,gender),m_sid(id)
{
    std::print("创建学生用户\n");
}
string Student::getStudentId() const
{
    return m_sid;
}

void addCourse(shared_ptr<Class> cla)
{
    m_selected_courses.pushback(cla);
}
