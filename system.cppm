// Module System
// File: system.cpp   Version: 0.1.0   License: AGPLv3
// Created:  YuHaoRan     2026-01-16 14:53:08
// Description:系统类，相当于管理人员，负责程序的一切执行
//

export module gradesystem:system;
import std;
import :student;
import :teacher;
import :course;



using std::string; using std::vector;
using std::shared_ptr; using std::weak_ptr;

export class System
{
public:
    System() = default;
    static System& singletonSystem();

    vector<shared_ptr<Teacher>>& getTeacherList();//获得老师
    vector<shared_ptr<Student>>& getStudentList();//获得学生
    vector<shared_ptr<Course>>& getCourseList();//获得课程

    void exec();//程序执行函数，所有操作放在这里面
private:
    vector<shared_ptr<Teacher>> _allTeachers;
    vector<shared_ptr<Student>> _allStudents;
    vector<shared_ptr<Course>> _allCourses;
};

System& System::singletonSystem()
{
    static System instance;
    return instance;
}

vector<shared_ptr<Teacher>>& System::getTeacherList() { return _allTeachers; }
vector<shared_ptr<Student>>& System::getStudentList() { return _allStudents; }
vector<shared_ptr<Course>>& System::getCourseList()   { return _allCourses; }
