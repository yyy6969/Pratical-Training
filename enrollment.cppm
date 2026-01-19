// Module enrollment
// File: enrollment.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 15:43:36
// Description:添加课程模块，用课程id号和学生id号进行匹配查找
//
export module gradesystem:enrollment;
import std;
import :course;
import :student;
import :studentbroker;
import :system;

using std::string; using std::vector;
using std::shared_ptr;using std::weak_ptr;

export class Enrollment
{
public:
    Enrollment();//初始化函数
    static Enrollment& singletonEnroll();
    void studentEnrollCourse(string sid,string cid);//完成学生添加课程
private:
};

Enrollment::Enrollment()
{
}

Enrollment& Enrollment::singletonEnroll()
{
    static Enrollment instance;
    return instance;
}


void Enrollment::studentEnrollCourse(string sid,string cid)
{
    studentBroker broker;
    auto& studentList = System::singletonSystem().getStudentList();
    auto& courseList = System::singletonSystem().getCourseList();

    shared_ptr<Student> stu = broker.findStudentById(sid, studentList);
    shared_ptr<Course> cla = broker.findCourseById(cid, courseList);
    if (!stu) {
        std::print("学生ID= {} 不存在！\n", sid);
        return; // 空指针时终止函数，避免崩溃
    }
    if (!cla) {
        std::print("课程ID= {} 不存在！\n", cid);
        return;
    }

    stu->studentAddCourse(cla);
    cla->studentAdd(weak_ptr<Student>(stu));
}
