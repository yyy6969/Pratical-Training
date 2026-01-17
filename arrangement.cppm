// Module
// File: main.cpp   Version: 0.1.0   License: AGPLv3
// Created:       2026-01-17 15:22:41
// Description:
//
export module arrangement;
import std;
import teacherbroker;
import system;

export class Arrangement
{
public:
    Arrangement(System& sys);//初始化函数
    static Arrangement& singletonArrange();
    void teacherArrangeCourse();
private:
    vector<shared_ptr<Class>> _courseList;
    vector<share_ptr<Teahcer>> _teacherList
};

Arrangement::Arrangement(System& sys)
{
    _courseList = sys.getTeacherList();
}

Arrangement& Arrangement::singletonArrange()
{
    static Arrangement instance;
    return instance;
}

void Arrangement::teacherArrangeCourse()
{
    teacherBroker broker;
    shared_ptr<Teacher> tea = broker.findTeacherById();
    shared_ptr<Class> cla = boker.findCourseById();

    tea.addCourse(cla);
    cla.teacherAdd(tea);
}
