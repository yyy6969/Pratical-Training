// Module   class
// File: class.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 14:58:16
// Description:课程类，有课程名、课程id号、学分以及统计该课程选人人数的统计量这几个属性
//
export module Class;
import std;
import student;
import teacher;

using std::string; using std::vector;
using std::weak_ptr;


export class Class
{
public:
    Class(string csName,string csId,double credit);
    string getid() const;//读取课程号
private:
    string m_courseName;
    string m_courseId;
    double m_credit;
    static int cm_totalCount;//静态数据，整个类共享，统计课的数量
    vector<weak_ptr<class Student>> _student;//用weak_ptr存储选课学生，不拥有所有权
    vector<weak_ptr<class Teacher>> _teacher;
};

int Class::cm_totalCount = 0;//课程数目初始化为零

Class::Class(string csName,string csId,double credit)
:m_courseName(csName),m_courseId(csId),m_credit(credit)
{
    cm_totalCount++;//课程数量加一
}

string Class::getid() const
{
    return m_courseId;
}
