// Module
// File: main.cpp   Version: 0.1.0   License: AGPLv3
// Created:       2026-01-17 15:22:41
// Description:
//
export module gradesystem:arrangement;
import std;
import :teacherbroker;
import :course;
import :teacher;
import :system;

using std::vector; using std::shared_ptr;
using std::string; using std::weak_ptr;

export class Arrangement
{
public:
    Arrangement() = default;//初始化函数
    static Arrangement& singletonArrange();
    void teacherArrangeCourse(string tid,string cid);
private:
    //vector<shared_ptr<Course>> _courseList;
    //vector<shared_ptr<Teacher>> _teacherList;
};

Arrangement& Arrangement::singletonArrange()
{
    static Arrangement instance;
    return instance;
}

void Arrangement::teacherArrangeCourse(string tid,string cid)
{
    teacherBroker broker;
    auto& teacherList = System::singletonSystem().getTeacherList();
    auto& courseList = System::singletonSystem().getCourseList();

    shared_ptr<Teacher> tea = broker.findTeacherById(tid, teacherList);
    shared_ptr<Course> cla = broker.findCourseById(cid, courseList);

    if (!tea) {
                std::print("教师ID= {} 不存在！",tid);
            }
            if (!cla) {
                std::print("课程ID= {} 不存在！",cid);
            }
    tea->teacherAddCourse(cla);
    cla->teacherAdd(weak_ptr<Teacher>(tea));
}
