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
    vector<Student>& getStudentList();
    const vector<Student>& getStudentListConst() const;// 获取学生列表,只读，防止误修改
    vector<Class>& getCourseLis();
    const vector<Class>& getCourseListConst();//获取学生列表，只读



    void exec();//程序执行函数，所有操作放在这里面
private:
    vector<share_ptr<Student>> _studentList;
    vector<share_ptr<Class>> _courseList;
    vector<share_ptr<Teahcer>> _teacherList
};

System::System()
{}

System& System::singletonSystem()
{
    static System instance;
    return instance;
}

vector<Student>& System::getStudentList()
{
    return _studentList;//得到学生数组并进行操作
}

const vector<Student>& getStudentListConst() const
{
    return _studentList;//获得只读数组，用于ui模块
}

vector<Class>& System::getCourseLis()
{
    return _courseList;
}

const vector<Class>& System:getCourseListConst()
{
    return _courseList;
}
