// Module
// File: main.cpp   Version: 0.1.0   License: AGPLv3
// Created:       2026-01-17 15:22:41
// Description:
//
export module arrangement;
import std;
import teacherbroker;
import Class;
import teacher;
import system;

using std::vector; using std::shared_ptr;
using std::string;

export class Arrangement
{
public:
    Arrangement(System& sys);//初始化函数
    static Arrangement& singletonArrange(System& sys);
    void teacherArrangeCourse(string tid,string cid);
private:
    vector<shared_ptr<Class>> _courseList;
    vector<shared_ptr<Teacher>> _teacherList;
};

Arrangement::Arrangement(System& sys)
{
    _courseList = sys.getCourseList();
    _teacherList = sys.getTeacherList();
}

Arrangement& Arrangement::singletonArrange(System& sys)
{
    static Arrangement instance(sys);
    return instance;
}

void Arrangement::teacherArrangeCourse(string tid,string cid)
{
    teacherBroker broker;
    shared_ptr<Teacher> tea = broker.findTeacherById(tid,_teacherList);
    shared_ptr<Class> cla = broker.findCourseById(cid,_courseList);

    tea->addCourse(cla);
    cla->teacherAdd(tea);
}
