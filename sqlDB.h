// Module   sqlDB
// File: sqlDB.h   Version: 0.1.0   License: AGPLv3
// Created:   YuHaoRan    2026-01-17 16:19:17
// Description:数据库模块头文件（仅声明）
//

#ifndef SQLDB_H
#define SQLDB_H

// 包含最小依赖头文件（仅用于声明）
#include <pqxx/pqxx>
#include <string>

// 命名空间封装，避免全局命名冲突
namespace sqlDB {

// 数据库操作类纯声明
class operationToDB
{
public:
    // 构造函数声明（参数用const&避免拷贝，更规范）
    operationToDB(const std::string& name, const std::string& user, const std::string& password);

    // 成员函数声明
    void createAllTables();  // 一键创建学生、教师、课程表
    bool insertPerson(const std::string& table_name, const std::string& id, const std::string& name, int age, const std::string& gender); // 插入学生/教师
    bool insertCourse(const std::string& id, const std::string& course_no, const std::string& course_name, double credit); // 插入课程
    bool insertUserCourseRelation(const std::string& user_id, const std::string& user_type, const std::string& course_id);
    bool insertStudentCourseRelation(const std::string& student_id, const std::string& course_id);
    bool insertTeacherCourseRelation(const std::string& teacher_id, const std::string& course_id);

private:
    // 私有函数声明
    pqxx::connection getConnection(); // 连接数据库函数

    // 成员变量声明
    std::string m_dbname;
    std::string m_user;
    std::string m_password;
    const std::string m_host = "127.0.0.1";
    const int m_port = 5432;
};

} // namespace sqlDB

#endif // SQLDB_H
