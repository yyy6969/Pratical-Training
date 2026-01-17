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
    void createStudentTable();//创建学生表
    void createTeacherTable();//创建老师表
    void createCourseTable();//创建课程表
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
}

void operationToDB::createStudentTable()
{
    try {
        auto conn = getConnection();
        pqxx::work txn(conn);

        string sql = R"(
           CREATE TABLE IF NOT EXISTS courses (
               id SERIAL PRIMARY KEY,
               course_name VARCHAR(100) NOT NULL UNIQUE,
               credit NUMERIC(3,1) CHECK (credit >= 0)
           );
       )";

       txn.exec(sql);
       txn.commit();
       std::cout << "课程表创建成功（或已存在）" << std::endl;
   } catch (const std::exception& e) {
       std::cerr << "创建课程表失败: " << e.what() << std::endl;
       throw;
   }
}

void operationToDB::createTeacherTable()
{
    try {
            auto conn = getConnection();
            pqxx::work txn(conn);

            // 移除原course_id字段，改为通过course_teacher_relation表关联
            string sql = R"(
                CREATE TABLE IF NOT EXISTS teachers (
                    id SERIAL PRIMARY KEY,
                    name VARCHAR(50) NOT NULL,
                    age SMALLINT CHECK (age > 0),
                    gender VARCHAR(10) CHECK (gender IN ('男', '女', '未知'))
                );
            )";

            txn.exec(sql);
            txn.commit();
            std::cout << "教师表创建成功（或已存在）" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "创建教师表失败: " << e.what() << std::endl;
            throw;
   }
}

void operationToDB::createCourseTable()
{
    try {
            auto conn = getConnection();
            pqxx::work txn(conn);

            string sql = R"(
                CREATE TABLE IF NOT EXISTS courses (
                    id SERIAL PRIMARY KEY,
                    course_name VARCHAR(100) NOT NULL UNIQUE,
                    credit NUMERIC(3,1) CHECK (credit >= 0)
                );
            )";

            txn.exec(sql);
            txn.commit();
            std::cout << "课程表创建成功（或已存在）" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "创建课程表失败: " << e.what() << std::endl;
            throw;
        }
}
