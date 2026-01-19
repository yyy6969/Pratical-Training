// Module   student
// File: student.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 14:55:54
// Description:学生类，进行选课操作
//
// Change Log:
//     [v0.1.1] YuHaoRan  2026-01-17 18:04:48
//         * 添加了获得所选课程的id号的函数
export module student;
import std;
import course;
import person;


using std::string; using std::vector;
using std::shared_ptr;

export class Student : public Person
{
public:
    Student(string name,int age,string gender,string id);
    string getStudentId() const;
    void studentAddCourse(shared_ptr<Course> cla);
private:
    string m_sid;
    vector<std::shared_ptr<Course>> m_selected_courses;//所选的课程
};

Student::Student(string name,int age,string gender,string id)
:Person(name,age,gender),m_sid(id)
{
    std::print("创建学生用户{}\n",name);
}

string Student::getStudentId() const
{
    return m_sid;
}

void Student::studentAddCourse(shared_ptr<Course> cla)//学生添加课程
{
    if (!cla) {
        print("【错误】学生{}（ID={}）：传入空课程对象，选课失败！\n",this->getName(), m_sid);
        return;
    }
    m_selected_courses.push_back(cla);
}


