// Module System
// File: system.cpp   Version: 0.1.0   License: AGPLv3
// Created:  YuHaoRan     2026-01-16 14:53:08
// Description:系统类，相当于管理人员，负责程序的一切执行
//

export module system;
import std;
import student;
import teacher;
import Class;

using std::string; using std::vector;
using std::shared_ptr; using std::weak_ptr;

export class System
{
public:
    System();
    static System& singletonSystem();
    //void exec() 执行函数

    vector<shared_ptr<Student>>& getStudentList();
    const vector<shared_ptr<Student>>& getStudentListConst() const; // 只读学生列表
    vector<shared_ptr<Teacher>>& getTeacherList();
    const vector<shared_ptr<Teacher>>& getTeacherListConst() const; // 只读教师列表
    vector<shared_ptr<Class>>& getCourseList();                     // 修复错误3：拼写 getCourseList
    const vector<shared_ptr<Class>>& getCourseListConst() const;    // 只读课程列表



    void exec();//程序执行函数，所有操作放在这里面
private:
    vector<shared_ptr<Student>> _studentList;
    vector<shared_ptr<Class>> _courseList;
    vector<shared_ptr<Teacher>> _teacherList;
};

System::System()
{}

System& System::singletonSystem()
{
    static System instance;
    return instance;
}


vector<shared_ptr<Student>>& System::getStudentList()
{
    return _studentList;
}

const vector<shared_ptr<Student>>& System::getStudentListConst() const
{
    return _studentList;
}

vector<shared_ptr<Teacher>>& System::getTeacherList()
{
    return _teacherList;
}

const vector<shared_ptr<Teacher>>& System::getTeacherListConst() const
{
    return _teacherList;
}

vector<shared_ptr<Class>>& System::getCourseList()
{
    return _courseList;
}

const vector<shared_ptr<Class>>& System::getCourseListConst() const
{
    return _courseList;
}

