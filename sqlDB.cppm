// Module   sqlDB
// File: sqlDB.cpp   Version: 0.1.0   License: AGPLv3
// Created:   YuHaoRan    2026-01-17 16:19:17
// Description:数据库模块,将数据库连接到本地
//

export module sqlDB;


import std;
import student;
import teacher;
import Class;
#include <pqxx/pqxx>


using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::to_string;

export class operationToDB
{
public:
    operationToDB(string name,string user,string password);

    void createAllTables();  // 一键创建学生、教师、课程表

    bool insertPerson(const string& table_name,string id,string name,int age,string gender); // 插入学生/教师
    bool insertCourse(string id, string course_no, string course_name, double credit);//插入课程

    bool insertUserCourseRelation(const string& user_id, const string& user_type, const string& course_id);

    bool insertStudentCourseRelation(const string& student_id, const string& course_id);
    bool insertTeacherCourseRelation(const string& teacher_id, const string& course_id);
private:
    pqxx::connection getConnection();//连接数据库函数
    string m_dbname;
    string m_user;
    string m_password;
    const string m_host = "127.0.0.1";
    const int m_port = 5432;
};

operationToDB::operationToDB(string name,string user,string password)
:m_dbname(name),m_user(user),m_password(password)
{
    try {
            auto conn = getConnection();
            if (conn.is_open()) {
                cout << "[INFO] 数据库连接成功: " << m_dbname << endl;
                conn.close();
            }
        } catch (const std::exception& e) {
            cerr << "[ERROR] 数据库连接失败: " << e.what() << endl;
            throw;
        }
}

pqxx::connection operationToDB::getConnection()
{
    string conn_str = "dbname = " + m_dbname +
                        " user = " + m_user +
                        " password = " + m_password +
                        " hostaddr = " + m_host +
                        " port = " + to_string(m_port);

        pqxx::connection conn(conn_str);
        if (!conn.is_open()) {
            throw std::runtime_error("无法打开数据库连接");
        }
    return conn;
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

    // 4. 重构：通用用户-课程关联表（替代原student_course）
        // 新增user_type字段区分"student"/"teacher"，支持学生选课、教师排课
        string create_user_course_sql = R"(
            CREATE TABLE IF NOT EXISTS user_course (
                user_id VARCHAR(50) NOT NULL,       -- 学生/教师ID
                user_type VARCHAR(10) NOT NULL CHECK (user_type IN ('student', 'teacher')), -- 类型标识
                course_id VARCHAR(50) NOT NULL,     -- 课程ID
                PRIMARY KEY (user_id, user_type, course_id), -- 联合主键：避免同一用户重复关联同一课程
                FOREIGN KEY (course_id) REFERENCES courses(id) ON DELETE CASCADE
            );
        )";

        // 执行建表语句
        txn.exec(create_student_sql);
        txn.exec(create_teacher_sql);
        txn.exec(create_course_sql);
        txn.exec(create_user_course_sql);
        txn.commit();

        cout << "[INFO] 所有表（学生、教师、课程）创建成功（或已存在）" << endl;
    } catch (const std::exception& e) {
        cerr << "[ERROR] 建表失败: " << e.what() << endl;
        throw;
    }
}

bool operationToDB::insertPerson(const string& table_name,string id,string name,int age,string gender)
{
    try {
            auto conn = getConnection();
            pqxx::work txn(conn);

            // 拼接插入SQL（动态表名）
            string sql = R"(
                INSERT INTO )" + table_name + R"( (id, name, age, gender)
                VALUES ($1, $2, $3, $4)
                ON CONFLICT (id) DO NOTHING
                RETURNING id;
            )";

             // 直接绑定独立参数，无需数组
            pqxx::result res = txn.exec_params(sql, id, name, age, gender);
            txn.commit();

            // 判断插入结果
            if (res.empty()) {
                cout << "[INFO] " << table_name << " 中ID=" << id << " 已存在，未插入" << endl;
                return false;
            }
            cout << "[INFO] " << table_name << " 插入成功: ID=" << id << " 姓名=" << name << endl;
            return true;
        } catch (const std::exception& e) {
            cerr << "[ERROR] 插入" << table_name << "失败: " << e.what() << endl;
            throw;
        }
}

bool operationToDB::insertCourse(string id, string course_no, string course_name, double credit)
{
    try {
            auto conn = getConnection();
            pqxx::work txn(conn);

            string sql = R"(
                INSERT INTO courses (id, course_no, course_name, credit)
                VALUES ($1, $2, $3, $4)
                ON CONFLICT (id) DO NOTHING
                RETURNING id;
            )";

            pqxx::result res = txn.exec_params(sql, id, course_no, course_name, credit);
            txn.commit();

            if (res.empty()) {
                cout << "[INFO] courses 中ID=" << id << " 已存在，未插入" << endl;
                return false;
            }
            cout << "[INFO] courses 插入成功: ID=" << id << " 课程名=" << course_name << endl;
            return true;
        } catch (const std::exception& e) {
            cerr << "[ERROR] 插入课程失败: " << e.what() << endl;
            throw;
        }
}

bool operationToDB::insertUserCourseRelation(const string& user_id, const string& user_type, const string& course_id)
{
// 校验用户类型
    if (user_type != "student" && user_type != "teacher") {
        cerr << "[ERROR] 无效的用户类型，仅支持 student/teacher" << endl;
        return false;
    }

    try {
        auto conn = getConnection();
        pqxx::work txn(conn);

        // 1. 校验用户是否存在
        string check_user_sql = (user_type == "student")
            ? "SELECT id FROM students WHERE id = $1;"
            : "SELECT id FROM teachers WHERE id = $1;";
        pqxx::result user_res = txn.exec_params(check_user_sql, user_id);
        if (user_res.empty()) {
            cerr << "[ERROR] " << user_type << " ID=" << user_id << " 不存在" << endl;
            txn.abort();
            return false;
        }

        // 2. 校验课程是否存在
        string check_course_sql = "SELECT id FROM courses WHERE id = $1;";
        pqxx::result course_res = txn.exec_params(check_course_sql, course_id);
        if (course_res.empty()) {
            cerr << "[ERROR] 课程ID=" << course_id << " 不存在" << endl;
            txn.abort();
            return false;
        }

        // 3. 插入关联关系
        string insert_sql = R"(
            INSERT INTO user_course (user_id, user_type, course_id)
            VALUES ($1, $2, $3)
            ON CONFLICT (user_id, user_type, course_id) DO NOTHING;
        )";
        pqxx::result res = txn.exec_params(insert_sql, user_id, user_type, course_id);
        txn.commit();

        if (res.affected_rows() > 0) {
            cout << "[INFO] 关联成功：" << user_type << " " << user_id << " - 课程 " << course_id << endl;
            return true;
        } else {
            cout << "[INFO] 关联已存在：" << user_type << " " << user_id << " - 课程 " << course_id << endl;
            return false;
        }
    } catch (const std::exception& e) {
        cerr << "[ERROR] 保存用户-课程关联失败: " << e.what() << endl;
        throw;
    }
}

// 学生选课：封装通用函数
bool operationToDB::insertStudentCourseRelation(const string& student_id, const string& course_id)
{
    return insertUserCourseRelation(student_id, "student", course_id);
}

// 教师排课：封装通用函数
bool operationToDB::insertTeacherCourseRelation(const string& teacher_id, const string& course_id)
{
    return insertUserCourseRelation(teacher_id, "teacher", course_id);
}
