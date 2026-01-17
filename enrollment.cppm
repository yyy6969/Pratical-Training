// Module enrollment
// File: enrollment.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 15:43:36
// Description:添加课程模块，用课程id号和学生id号进行匹配查找
//
export module enrollment;
import std;
import Class;
import student;
import studentbroker;
import system;

using std::string; using std::vector;
using std::shared_ptr;

export class Enrollment
{
public:
    Enrollment(System& sys);//初始化函数
    static Enrollment& singletonEnroll(System& sys);
    void studentEnrollCourse(string sid,string cid);//完成学生添加课程
private:
    vector<shared_ptr<Student>> _studentList;
    vector<shared_ptr<Class>> _courseList;
};

Enrollment::Enrollment(System& sys)
{
    _studentList = sys.getStudentList();
    _courseList = sys.getCourseList();
}

Enrollment& Enrollment::singletonEnroll(System& sys)
{
    static Enrollment instance(sys);
    return instance;
}

void Enrollment::studentEnrollCourse(string sid,string cid)
{
    studentBroker broker;
    shared_ptr<Student> stu = broker.findStudentById(sid,_studentList);
    shared_ptr<Class> cla = broker.findCourseById(cid,_courseList);

    stu->addCourse(cla);
    cla->addStudent(stu);
}
