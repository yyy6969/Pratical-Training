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
import person;


using std::string; using std::vector;
using std::shared_ptr;

export class Student : public Person
{
public:
    Student(string name,int age,string gender,string id);
    string getStudentId() const;
    void addCourse(class Class cla);
    vector<int> getSelectedCourseIds() const;//提取所选课程的ID数组（用于插入数据库）
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

void addCourse(shared_ptr<class Class> cla)
{
    m_selected_courses.pushback(cla);
}

vector<int> Student::getSelectedCourseIds() const
{
    vector<int> course_ids;
    for (const auto& course_ptr : m_selected_courses) {
        course_ids.push_back(course_ptr->getId()); // 从Course对象中提取ID
    }
    return course_ids;
}
