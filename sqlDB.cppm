// Module   sqlDB
// File: sqlDB.cpp   Version: 0.1.0   License: AGPLv3
// Created:   YuHaoRan    2026-01-17 16:19:17
// Description:数据库模块,将数据库连接到本地
//

export module sqlDB;
import std;
#include <pqxx/pqxx>

using std::string;

export class operationToDB
{
public:
    operationToDB(string name,string user,string password);

    void createAllTables();  // 一键创建学生、教师、课程表

    // 插入课程：指定课程ID(字符型)、课程编号、课程名、学分
    bool insertCourse(const string& course_id, const string& course_no, const string& course_name, double credit);
    // 插入学生：指定学号、姓名、年龄、性别、关联课程ID列表
    bool insertStudent(const string& student_no, const string& name, int age, const string& gender, const vector<string>& course_ids = {});
    // 插入教师：指定教师编号、姓名、年龄、性别、关联课程ID
    bool insertTeacher(const string& teacher_no, const string& name, int age, const string& gender, const string& course_id = "");
private:
    pqxx::connection getConnection();//连接数据库函数
    string m_dbname;
    string m_user;
    string m_password;
}

operationToDB::operationToDB(string name,string user,string password)
:m_dbname(name),m_user(user),m_password(password)
{
}

pqxx::connection operationToDB::getConnection()
{
    // 构造PostgreSQL连接字符串
    string address ="dbname = " + m_dbname + " user=" + m_user + " password="+m_password+" hostaddr=127.0.0.1 port=5432";
    connection C(address);
    if (C.is_open()) {
        cout << "Opened database successfully: " << C.dbname() << endl;
    }else {
        cout << "Can't open database" << endl;
    }
    return C;
}

void operationToDB::createAllTables()
{
    try {
        auto conn = getConnection();
        pqxx::work txn(conn);

        // 1. 创建学生表
        string create_student_sql = R"(
            CREATE TABLE IF NOT EXISTS students (
                id VARCHAR(50) NOT NULL PRIMARY KEY,  -- 学生ID（字符型，用户指定）
                name VARCHAR(50) NOT NULL,            -- 姓名
                age SMALLINT CHECK (age > 0),         -- 年龄
                gender VARCHAR(10) CHECK (gender IN ('男', '女', '未知')) -- 性别
            );
        )";

        // 2. 创建教师表
        string create_teacher_sql = R"(
            CREATE TABLE IF NOT EXISTS teachers (
                id VARCHAR(50) NOT NULL PRIMARY KEY,  -- 教师ID（字符型，用户指定）
                name VARCHAR(50) NOT NULL,            -- 姓名
                age SMALLINT CHECK (age > 0),         -- 年龄
                gender VARCHAR(10) CHECK (gender IN ('男', '女', '未知')) -- 性别
            );
        )";

        // 3. 创建课程表
        string create_course_sql = R"(
            CREATE TABLE IF NOT EXISTS courses (
                id VARCHAR(50) NOT NULL PRIMARY KEY,  -- 课程ID（字符型，用户指定）
                course_no VARCHAR(20) NOT NULL UNIQUE,-- 课程编号
                course_name VARCHAR(100) NOT NULL,    -- 课程名
                credit NUMERIC(3,1) CHECK (credit >= 0) -- 学分
            );
        )";

        // 执行建表语句
        txn.exec(create_student_sql);
        txn.exec(create_teacher_sql);
        txn.exec(create_course_sql);
        txn.commit();

        cout << "[INFO] 所有表（学生、教师、课程）创建成功（或已存在）" << endl;
    } catch (const std::exception& e) {
        cerr << "[ERROR] 建表失败: " << e.what() << endl;
        throw;
    }
}
