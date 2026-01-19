// Module   ui
// File: ui.cppm   Version: 0.3.0   License: AGPLv3
// Created: YuHaoRan      2026-01-19 19:00:00
// Description:控制台UI类，保留核心功能，去掉冗余交互
//
export module gradesystem:ui;
import std;
import :system;
import :arrangement;
import :enrollment;
import database;

export class UI
{
public:
    // 单例模式
    static UI& singletonUI();

    // 核心功能
    void initSystem(const std::string& db_name, const std::string& db_user, const std::string& db_pwd); // 系统初始化（含基础数据）
    void showMainMenu();
    void run();                                   // 启动UI循环

private:
    UI() = default;
    ~UI() = default;
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;
    UI(UI&&) = delete;
    UI& operator=(UI&&) = delete;

    // 核心功能函数
    void addTeacher();                            // 添加教师
    void addStudent();                            // 添加学生
    void addCourse();                             // 添加课程
    void teacherArrangeCourse();                  // 教师排课
    void studentEnrollCourse();                   // 学生选课
    void printAllData();                          // 打印所有数据
    void initTestData();                          // 初始化基础测试数据

    // 工具函数
    std::string getInput(const std::string& prompt); // 获取用户输入
    int getIntInput(const std::string& prompt);      // 获取整数输入（带校验）
    double getDoubleInput(const std::string& prompt); // 获取浮点数输入（带校验）

    // 成员变量：数据库连接参数
    std::string m_db_name;
    std::string m_db_user;
    std::string m_db_pwd;
};

// 单例实现
UI& UI::singletonUI()
{
    static UI instance;
    return instance;
}

// 系统初始化：创建数据库表 + 预置基础测试数据
void UI::initSystem(const std::string& db_name, const std::string& db_user, const std::string& db_pwd)
{
    // 保存数据库参数
    m_db_name = db_name;
    m_db_user = db_user;
    m_db_pwd = db_pwd;

    std::cout << "===== 成绩管理系统初始化 =====\n";

    // 1. 初始化数据库（创建表）
    try {
        operationToDB db_op(m_db_name, m_db_user, m_db_pwd);
        db_op.createAllTables();
        std::cout << "[成功] 数据库表初始化完成！\n";
    } catch (const std::exception& e) {
        std::cerr << "[错误] 数据库初始化失败：" << e.what() << "\n";
        std::cerr << "系统无法启动，请检查数据库连接！\n";
        std::exit(1);
    }

    // 2. 预置基础测试数据
    try {
        initTestData();
        std::cout << "[成功] 基础测试数据初始化完成！\n";
    } catch (const std::exception& e) {
        std::cerr << "[警告] 基础数据初始化失败：" << e.what() << "\n";
    }

    std::cout << "[成功] 系统初始化完成！\n\n";
}

// 预置基础测试数据
void UI::initTestData()
{
    operationToDB db_op(m_db_name, m_db_user, m_db_pwd);
    auto& system = System::singletonSystem();
    auto& teacherList = system.getTeacherList();
    auto& studentList = system.getStudentList();
    auto& courseList = system.getCourseList();

    teacherList.clear();
    studentList.clear();
    courseList.clear();

    // 预置教师（英文性别）
    db_op.insertPerson("teachers", "T001", "Zhang San", 35, "man");
    db_op.insertPerson("teachers", "T002", "Li Si", 42, "woman");
    teacherList.emplace_back(std::make_shared<Teacher>("Zhang San", 35, "man", "T001"));
    teacherList.emplace_back(std::make_shared<Teacher>("Li Si", 42, "woman", "T002"));

    // 预置学生（英文性别）
    db_op.insertPerson("students", "S001", "Xiao Ming", 18, "man");
    db_op.insertPerson("students", "S002", "Xiao Hong", 19, "woman");
    studentList.emplace_back(std::make_shared<Student>("Xiao Ming", 18, "man", "S001"));
    studentList.emplace_back(std::make_shared<Student>("Xiao Hong", 19, "woman", "S002"));

    // 预置课程（无变化）
    db_op.insertCourse("C001", "CS001", "C++ Programming", 3.0);
    db_op.insertCourse("C002", "MA001", "Advanced Math", 4.0);
    courseList.emplace_back(std::make_shared<Course>("C++ Programming", "C001", 3.0));
    courseList.emplace_back(std::make_shared<Course>("Advanced Math", "C002", 4.0));
}

// 主菜单
void UI::showMainMenu()
{
    std::cout << "===== 成绩管理系统 =====\n";
    std::cout << "1. 添加教师\n2. 添加学生\n3. 添加课程\n";
    std::cout << "4. 教师排课\n5. 学生选课\n6. 查看所有数据\n";
    std::cout << "0. 退出系统\n";
    std::cout << "默认数据：教师(T001/T002) | 学生(S001/S002) | 课程(C001/C002)\n";
    std::cout << "请输入操作编号：";
}

// 启动UI循环
void UI::run()
{
    int choice = -1;
    while (true) {
        showMainMenu();
        choice = getIntInput("");

        switch (choice) {
            case 1: addTeacher(); break;
            case 2: addStudent(); break;
            case 3: addCourse(); break;
            case 4: teacherArrangeCourse(); break;
            case 5: studentEnrollCourse(); break;
            case 6: printAllData(); break;
            case 0:
                std::cout << "感谢使用，再见！\n";
                return;
            default:
                std::cout << "无效编号，请重新输入！\n\n";
                break;
        }
    }
}

// 添加教师
void UI::addTeacher()
{
    std::cout << "\n===== 添加教师 =====\n";
    std::string tid = getInput("教师ID：");
    std::string name = getInput("姓名：");
    int age = getIntInput("年龄：");
    std::string gender = getInput("性别（man/woman/unknown）："); // 提示英文输入

    try {
        operationToDB db_op(m_db_name, m_db_user, m_db_pwd);
        bool res = db_op.insertPerson("teachers", tid, name, age, gender);
        if (res) {
            // 数据库插入成功 → 同步添加到System的教师列表
            auto& system = System::singletonSystem();
            system.getTeacherList().emplace_back(std::make_shared<Teacher>(name, age, gender, tid));
            std::cout << "教师添加成功（数据库+内存）！\n\n";
        } else {
            std::cout << "教师ID已存在！\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "添加失败：" << e.what() << "\n\n";
    }
}

// 添加学生
void UI::addStudent()
{
    std::cout << "\n===== 添加学生 =====\n";
    std::string sid = getInput("学生ID：");
    std::string name = getInput("姓名：");
    int age = getIntInput("年龄：");
    std::string gender = getInput("性别（man/woman/unknown）："); // 提示英文输入

    try {
        operationToDB db_op(m_db_name, m_db_user, m_db_pwd);
        bool res = db_op.insertPerson("students", sid, name, age, gender);
        if (res) {
            // 数据库插入成功 → 同步添加到System的学生列表
            auto& system = System::singletonSystem();
            system.getStudentList().emplace_back(std::make_shared<Student>(name, age, gender, sid));
            std::cout << "学生添加成功（数据库+内存）！\n\n";
        } else {
            std::cout << "学生ID已存在！\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "添加失败：" << e.what() << "\n\n";
    }
}

// 添加课程
void UI::addCourse()
{
    std::cout << "\n===== 添加课程 =====\n";
    std::string cid = getInput("课程ID：");
    std::string course_no = getInput("课程编号：");
    std::string course_name = getInput("课程名称：");
    double credit = getDoubleInput("学分：");

    try {
        operationToDB db_op(m_db_name, m_db_user, m_db_pwd);
        bool res = db_op.insertCourse(cid, course_no, course_name, credit);
        if (res) {
            // 数据库插入成功 → 同步添加到System的课程列表
            auto& system = System::singletonSystem();
            system.getCourseList().emplace_back(std::make_shared<Course>(course_name, cid, credit));
            std::cout << "课程添加成功（数据库+内存）！\n\n";
        } else {
            std::cout << "课程ID已存在！\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "添加失败：" << e.what() << "\n\n";
    }
}

// 教师排课
void UI::teacherArrangeCourse()
{
    std::cout << "\n===== 教师排课 =====\n";
    std::string tid = getInput("教师ID：");
    std::string cid = getInput("课程ID：");

    try {
        auto& arrange = Arrangement::singletonArrange();
        arrange.teacherArrangeCourse(tid, cid, m_db_name, m_db_user, m_db_pwd);
    } catch (const std::exception& e) {
        std::cerr << "排课失败：" << e.what() << "\n\n";
    }
}

// 学生选课
void UI::studentEnrollCourse()
{
    std::cout << "\n===== 学生选课 =====\n";
    std::string sid = getInput("学生ID：");
    std::string cid = getInput("课程ID：");

    try {
        auto& enroll = Enrollment::singletonEnroll();
        enroll.studentEnrollCourse(sid, cid, m_db_name, m_db_user, m_db_pwd);
    } catch (const std::exception& e) {
        std::cerr << "选课失败：" << e.what() << "\n\n";
    }
}

// 打印所有数据
void UI::printAllData()
{
    std::cout << "\n===== 所有数据 =====\n";
    auto& system = System::singletonSystem();

    // 教师
    std::cout << "【教师】\n";
    for (const auto& tea : system.getTeacherList()) {
        std::cout << "ID：" << tea->getTeacherId() << " | 姓名：" << tea->getName() << "\n";
    }

    // 学生
    std::cout << "\n【学生】\n";
    for (const auto& stu : system.getStudentList()) {
        std::cout << "ID：" << stu->getStudentId() << " | 姓名：" << stu->getName() << "\n";
    }

    // 课程
    std::cout << "\n【课程】\n";
    for (const auto& course : system.getCourseList()) {
        std::cout << "ID：" << course->getid() << " | 名称：" << course->getName() << "\n";
    }
    std::cout << "\n";
}

// 工具函数：获取字符串输入
std::string UI::getInput(const std::string& prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    // 去除首尾空格
    input.erase(input.find_last_not_of(" \t") + 1);
    input.erase(0, input.find_first_not_of(" \t"));
    return input;
}

// 工具函数：获取整数输入
int UI::getIntInput(const std::string& prompt)
{
    int num = 0;
    while (true) {
        std::string input = getInput(prompt);
        try {
            num = std::stoi(input);
            break;
        } catch (...) {
            std::cout << "请输入整数：";
        }
    }
    return num;
}

// 工具函数：获取浮点数输入
double UI::getDoubleInput(const std::string& prompt)
{
    double num = 0.0;
    while (true) {
        std::string input = getInput(prompt);
        try {
            num = std::stod(input);
            break;
        } catch (...) {
            std::cout << "请输入数字：";
        }
    }
    return num;
}
