// Module enrollment
// File: enrollment.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 15:43:36
// Description:添加课程模块，用课程id号和学生id号进行匹配查找（对接数据库持久化）
//
export module gradesystem:enrollment;
import std;
import :course;
import :student;
import :studentbroker;
import :system;
// 新增：导入数据库模块
import database;

using std::string; using std::vector;
using std::shared_ptr;using std::weak_ptr;

export class Enrollment
{
public:
    Enrollment();
    static Enrollment& singletonEnroll();
    void studentEnrollCourse(string sid, string cid,
                             const string& db_name = "gradeSystem",
                             const string& db_user = "postgres",
                             const string& db_pwd = "postgres");
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

void Enrollment::studentEnrollCourse(string sid, string cid,
                                     const string& db_name,
                                     const string& db_user,
                                     const string& db_pwd)
{
    studentBroker broker;
    auto& studentList = System::singletonSystem().getStudentList();
    auto& courseList = System::singletonSystem().getCourseList();

    shared_ptr<Student> stu = broker.findStudentById(sid, studentList);
    shared_ptr<Course> cla = broker.findCourseById(cid, courseList);

    if (!stu) {
        std::print("学生ID= {} 不存在！\n", sid);
        return;
    }
    if (!cla) {
        std::print("课程ID= {} 不存在！\n", cid);
        return;
    }

    stu->studentAddCourse(cla);
    cla->studentAdd(weak_ptr<Student>(stu));
    std::print("内存中学生{}已选课程{}\n", sid, cid);

    try {
        operationToDB db_op(db_name, db_user, db_pwd);
        // 调用数据库模块的学生-课程关联接口
        bool res = db_op.insertStudentCourseRelation(sid, cid);
        if (res) {
            std::print("数据库中学生{}选课{}成功！\n", sid, cid);
        } else {
            std::print("数据库中学生{}已选课程{}，无需重复添加\n", sid, cid);
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] 学生选课写入数据库失败：" << e.what() << "\n";
    }
}
