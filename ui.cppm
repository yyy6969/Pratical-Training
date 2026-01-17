//duruoxian
//2024051604062
//UI模块接口单元
// ui.cppm - 版本1：基础UI框架
// 此版本实现基本的数据展示功能，展示系统核心架构
export module ui;

import std;
import system;          // 系统核心模块
import student;         // 学生模块
import teacher;         // 教师模块
import Class;           // 课程模块

using std::string;
using std::vector;
using std::shared_ptr;
using std::cin;
using std::getline;

export class UI_Basic {
private:
    System& system;  // 系统核心引用

    // 暂停等待用户输入
    void pause() {
        std::print("\n按Enter键继续...");
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }

    // 获取字符串输入
    string getStringInput(const string& prompt) {
        string input;
        std::print("{}", prompt);
        getline(cin, input);
        return input;
    }

    // 获取整数输入
    int getIntInput(const string& prompt) {
        int value;
        while (true) {
            std::print("{}", prompt);
            if (cin >> value) {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::print("输入无效，请输入整数！\n");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // 获取浮点数输入
    double getDoubleInput(const string& prompt) {
        double value;
        while (true) {
            std::print("{}", prompt);
            if (cin >> value) {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::print("输入无效，请输入数字！\n");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

public:
    // 构造函数：初始化系统引用
    UI_Basic() : system(System::singletonSystem()) {}

    // 运行UI主循环
    void run() {
        while (true) {
            int choice = showMainMenu();

            switch (choice) {
                case 1: displayAllStudents(); break;
                case 2: displayAllTeachers(); break;
                case 3: displayAllCourses(); break;
                case 4: displaySystemInfo(); break;
                case 5:
                    std::print("感谢使用，再见！\n");
                    return;
                default:
                    std::print("无效选择！\n");
            }
        }
    }

private:
    // 显示主菜单
    int showMainMenu() {
        std::print("========================================\n");
        std::print("      学生选课管理系统 - 基础版\n");
        std::print("========================================\n");
        std::print(" 1. 查看学生列表\n");
        std::print(" 2. 查看教师列表\n");
        std::print(" 3. 查看课程列表\n");
        std::print(" 4. 查看系统信息\n");
        std::print(" 5. 退出系统\n");
        std::print("========================================\n");

        return getIntInput("请选择操作 (1-5): ");
    }

    // 显示学生列表
    void displayAllStudents() {
        std::print("=== 学生列表 ===\n");

        // 获取学生列表
        const auto& students = system.getStudentList();

        if (students.empty()) {
            std::print("系统中没有学生。\n");
        } else {
            std::print("序号  学号        姓名        年龄  性别\n");
            std::print("----------------------------------------\n");

            for (size_t i = 0; i < students.size(); ++i) {
                auto stu = students[i];
                std::print("{:<5} {:<12} {:<10} {:<5} {:<5}\n",
                    i+1, stu->getStudentId(), stu->getName(),
                    stu->getAge(), stu->getGender());
            }
        }

        pause();
    }

    // 显示教师列表
    void displayAllTeachers() {
        std::print("=== 教师列表 ===\n");

        const auto& teachers = system.getTeacherList();

        if (teachers.empty()) {
            std::print("系统中没有教师。\n");
        } else {
            std::print("序号  工号        姓名        年龄  性别\n");
            std::print("----------------------------------------\n");

            for (size_t i = 0; i < teachers.size(); ++i) {
                auto tea = teachers[i];
                std::print("{:<5} {:<12} {:<10} {:<5} {:<5}\n",
                    i+1, tea->getTeacherId(), tea->getName(),
                    tea->getAge(), tea->getGender());
            }
        }

        pause();
    }

    // 显示课程列表
    void displayAllCourses() {
        std::print("=== 课程列表 ===\n");

        const auto& courses = system.getCourseList();

        if (courses.empty()) {
            std::print("系统中没有课程。\n");
        } else {
            std::print("序号  课程编号\n");
            std::print("--------------\n");

            for (size_t i = 0; i < courses.size(); ++i) {
                auto course = courses[i];
                std::print("{:<5} {}\n", i+1, course->getid());
            }
        }

        pause();
    }

    // 显示系统信息
    void displaySystemInfo() {
        std::print("=== 系统信息 ===\n");

        const auto& students = system.getStudentList();
        const auto& teachers = system.getTeacherList();
        const auto& courses = system.getCourseList();

        std::print("学生总数: {}\n", students.size());
        std::print("教师总数: {}\n", teachers.size());
        std::print("课程总数: {}\n", courses.size());

        pause();
    }
};
