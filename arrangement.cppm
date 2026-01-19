// Module
// File: main.cpp   Version: 0.1.0   License: AGPLv3
// Created:       2026-01-17 15:22:41
// Description: 教师排课模块（对接数据库持久化）
//
export module gradesystem:arrangement;
import std;
import :teacherbroker;
import :course;
import :teacher;
import :system;
// 新增：导入数据库模块
import database;

using std::vector; using std::shared_ptr;
using std::string; using std::weak_ptr;

export class Arrangement
{
public:
    Arrangement() = default;
    static Arrangement& singletonArrange();
    // 改造：添加数据库连接参数（或从配置读取，这里简化为固定参数）
    void teacherArrangeCourse(string tid, string cid,
                              const string& db_name = "gradeSystem",
                              const string& db_user = "postgres",
                              const string& db_pwd = "postgres");
private:
};

Arrangement& Arrangement::singletonArrange()
{
    static Arrangement instance;
    return instance;
}

void Arrangement::teacherArrangeCourse(string tid, string cid,
                                       const string& db_name,
                                       const string& db_user,
                                       const string& db_pwd)
{
    teacherBroker broker;
    auto& teacherList = System::singletonSystem().getTeacherList();
    auto& courseList = System::singletonSystem().getCourseList();

    shared_ptr<Teacher> tea = broker.findTeacherById(tid, teacherList);
    shared_ptr<Course> cla = broker.findCourseById(cid, courseList);

    if (!tea) {
        std::print("教师ID= {} 不存在！\n", tid);
        return;
    }
    if (!cla) {
        std::print("课程ID= {} 不存在！\n", cid);
        return;
    }

    tea->teacherAddCourse(cla);
    cla->teacherAdd(weak_ptr<Teacher>(tea));
    std::print("内存中教师{}已关联课程{}\n", tid, cid);

    try {
        operationToDB db_op(db_name, db_user, db_pwd);
        // 调用数据库模块的教师-课程关联接口
        bool res = db_op.insertTeacherCourseRelation(tid, cid);
        if (res) {
            std::print("数据库中教师{}排课{}成功！\n", tid, cid);
        } else {
            std::print("数据库中教师{}已关联课程{}，无需重复添加\n", tid, cid);
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] 教师排课写入数据库失败：" << e.what() << "\n";
    }
}
