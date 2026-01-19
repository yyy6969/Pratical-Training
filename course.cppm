// Module   course class
// File: course.cppm   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 14:58:16
// Description:课程类，核心属性：课程名、课程id、学分，支持添加学生/老师
//
export module gradesystem:course;
import std;

using std::string;
using std::vector;
using std::weak_ptr;

export class Course
{
public:
    // 构造函
    Course(string csName, string csId, double credit);

    string getid() const;          // 读取课程号
    string getName() const;             // 读取课程名字
    void studentAdd(weak_ptr<class Student> stu);  // 添加学生
    void teacherAdd(weak_ptr<class Teacher> tec);  // 添加老师

private:
    string m_courseName;           // 课程名称
    string m_courseId;             // 课程ID
    double m_credit;               // 学分（保留但无对外接口）

    // 存储学生/老师的容器（仅用于添加功能）
    vector<weak_ptr<class Student>> _student;
    vector<weak_ptr<class Teacher>> _teacher;
};

// 构造函数实现
Course::Course(string csName, string csId, double credit)
    : m_courseName(csName), m_courseId(csId), m_credit(credit)
{}

// 读取课程ID
string Course::getid() const
{
    return m_courseId;
}

// 读取课程名称
string Course::getName() const
{
    return m_courseName;
}

void Course::studentAdd(weak_ptr<class Student> stu) {
    _student.push_back(stu);
}

void Course::teacherAdd(weak_ptr<class Teacher> tec) {
    _teacher.push_back(tec);
}
