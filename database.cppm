// Module   sqlDB
// File: sqlDB.cppm   Version: 0.1.0   License: AGPLv3
// Created:   YuHaoRan    2026-01-17 16:19:17
// Description:数据库模块（C++20模块版）
//

module;
#include <pqxx/pqxx>

export module database;

import std;

// 数据库操作类
export class operationToDB
{
public:
    // 构造函数
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
    std::shared_ptr<pqxx::connection> getConnection(); // 连接数据库函数

    // 成员变量声明
    std::string m_dbname;
    std::string m_user;
    std::string m_password;
    const std::string m_host = "127.0.0.1";
    const int m_port = 5432;
};

operationToDB::operationToDB(const std::string& name, const std::string& user, const std::string& password)
    : m_dbname(name), m_user(user), m_password(password)
{
    try {
        auto conn = getConnection();
        if (conn->is_open()) {
            std::cout << "[INFO] 数据库连接成功: " << m_dbname << "\n";
            conn->close();
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] 数据库连接失败: " << e.what() << "\n";
        throw;
    }
}

// 私有函数：创建数据库连接实现
std::shared_ptr<pqxx::connection> operationToDB::getConnection()
{
    std::string conn_str = "dbname = " + m_dbname +
                      " user = " + m_user +
                      " password = " + m_password +
                      " hostaddr = " + m_host +
                      " port = " + std::to_string(m_port);

    auto conn = std::make_shared<pqxx::connection>(conn_str);
    if (!conn->is_open()) {
        throw std::runtime_error("无法打开数据库连接");
    }
    return conn;
}

// 一键创建所有表实现
void operationToDB::createAllTables()
{
    try {
        auto conn = getConnection();
        pqxx::work txn(*conn);

        // 1. 创建学生表
        std::string create_student_sql = R"(
            CREATE TABLE IF NOT EXISTS students (
                id VARCHAR(50) NOT NULL PRIMARY KEY,
                name VARCHAR(50) NOT NULL,
                age SMALLINT CHECK (age > 0),
                gender VARCHAR(10) CHECK (gender IN ('man', 'woman', 'unknown'))
            );
        )";

        // 2. 创建教师表
        std::string create_teacher_sql = R"(
            CREATE TABLE IF NOT EXISTS teachers (
                id VARCHAR(50) NOT NULL PRIMARY KEY,
                name VARCHAR(50) NOT NULL,
                age SMALLINT CHECK (age > 0),
                gender VARCHAR(10) CHECK (gender IN ('man', 'woman', 'unknown'))
            );
        )";

        // 3. 新增：课程表定义
        std::string create_course_sql = R"(
            CREATE TABLE IF NOT EXISTS courses (
                id VARCHAR(50) NOT NULL PRIMARY KEY,
                course_no VARCHAR(20) NOT NULL UNIQUE,
                course_name VARCHAR(100) NOT NULL,
                credit NUMERIC(3,1) CHECK (credit >= 0)
            );
        )";

        // 4. 通用用户-课程关联表
        std::string create_user_course_sql = R"(
            CREATE TABLE IF NOT EXISTS user_course (
                user_id VARCHAR(50) NOT NULL,       -- 学生/教师ID
                user_type VARCHAR(10) NOT NULL CHECK (user_type IN ('student', 'teacher')), -- 类型标识
                course_id VARCHAR(50) NOT NULL,     -- 课程ID
                PRIMARY KEY (user_id, user_type, course_id), -- 联合主键：避免同一用户重复关联同一课程
                FOREIGN KEY (course_id) REFERENCES courses(id) ON DELETE CASCADE
            );
        )";

        // 执行建表SQL
        txn.exec(create_student_sql);
        txn.exec(create_teacher_sql);
        txn.exec(create_course_sql);
        txn.exec(create_user_course_sql);
        txn.commit();

        std::cout << "[INFO] 所有表（学生、教师、课程）创建成功（或已存在）\n";
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] 建表失败: " << e.what() << "\n";
        throw;
    }
}


// 插入学生/教师实现
bool operationToDB::insertPerson(const std::string& table_name, const std::string& id, const std::string& name, int age, const std::string& gender)
{
    try {
        auto conn = getConnection();
        pqxx::work txn(*conn);

        // 拼接插入SQL（动态表名）
        std::string sql = R"(
            INSERT INTO )" + table_name + R"( (id, name, age, gender)
            VALUES ($1, $2, $3, $4)
            ON CONFLICT (id) DO NOTHING
            RETURNING id;
        )";

        pqxx::result res = txn.exec(sql, pqxx::params{id, name, age, gender});
        txn.commit();

        // 判断插入结果
        if (res.empty()) {
            std::cout << "[INFO] " << table_name << " 中ID=" << id << " 已存在，未插入\n";
            return false;
        }
        std::cout << "[INFO] " << table_name << " 插入成功: ID=" << id << " 姓名=" << name << "\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] 插入" << table_name << "失败: " << e.what() << "\n";
        throw;
    }
}

// 插入课程实现
bool operationToDB::insertCourse(const std::string& id, const std::string& course_no, const std::string& course_name, double credit)
{
    try {
        auto conn = getConnection();
        pqxx::work txn(*conn);

        std::string sql = R"(
            INSERT INTO courses (id, course_no, course_name, credit)
            VALUES ($1, $2, $3, $4)
            ON CONFLICT (id) DO NOTHING
            RETURNING id;
        )";

        pqxx::result res = txn.exec(sql, pqxx::params{id, course_no, course_name, credit});
        txn.commit();

        if (res.empty()) {
            std::cout << "[INFO] courses 中ID=" << id << " 已存在，未插入\n";
            return false;
        }
        std::cout << "[INFO] courses 插入成功: ID=" << id << " 课程名=" << course_name << "\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] 插入课程失败: " << e.what() << "\n";
        throw;
    }
}

// 通用用户-课程关联实现
bool operationToDB::insertUserCourseRelation(const std::string& user_id, const std::string& user_type, const std::string& course_id)
{
    // 校验用户类型
    if (user_type != "student" && user_type != "teacher") {
        std::cerr << "[ERROR] 无效的用户类型，仅支持 student/teacher\n";
        return false;
    }

    try {
        auto conn = getConnection();
        pqxx::work txn(*conn);

        // 1. 校验用户是否存在
        std::string check_user_sql = (user_type == "student")
            ? "SELECT id FROM students WHERE id = $1;"
            : "SELECT id FROM teachers WHERE id = $1;";
        pqxx::result user_res = txn.exec(check_user_sql, pqxx::params{user_id});
        if (user_res.empty()) {
            std::cerr << "[ERROR] " << user_type << " ID=" << user_id << " 不存在\n";
            txn.abort();
            return false;
        }

        // 2. 校验课程是否存在
        std::string check_course_sql = "SELECT id FROM courses WHERE id = $1;";
        pqxx::result course_res = txn.exec(check_course_sql, pqxx::params{course_id});
        if (course_res.empty()) {
            std::cerr << "[ERROR] 课程ID=" << course_id << " 不存在\n";
            txn.abort();
            return false;
        }

        // 3. 插入关联关系
        std::string insert_sql = R"(
            INSERT INTO user_course (user_id, user_type, course_id)
            VALUES ($1, $2, $3)
            ON CONFLICT (user_id, user_type, course_id) DO NOTHING;
        )";
        pqxx::result res = txn.exec(insert_sql, pqxx::params{user_id, user_type, course_id});
        txn.commit();

        if (res.affected_rows() > 0) {
            std::cout << "[INFO] 关联成功：" << user_type << " " << user_id << " - 课程 " << course_id << "\n";
            return true;
        } else {
            std::cout << "[INFO] 关联已存在：" << user_type << " " << user_id << " - 课程 " << course_id << "\n";
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] 保存用户-课程关联失败: " << e.what() << "\n";
        throw;
    }
}

// 学生选课：封装通用函数
bool operationToDB::insertStudentCourseRelation(const std::string& student_id, const std::string& course_id)
{
    return insertUserCourseRelation(student_id, "student", course_id);
}

// 教师排课：封装通用函数
bool operationToDB::insertTeacherCourseRelation(const std::string& teacher_id, const std::string& course_id)
{
    return insertUserCourseRelation(teacher_id, "teacher", course_id);
}
