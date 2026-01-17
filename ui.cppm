//duruoxian
//2024051604062
//UI模块接口单元
// ui.cppm - 学生选课管理系统UI模块

// 基于提供的10个模块实现
export module ui;

import std;
import system;          // 系统核心模块，管理学生、教师、课程列表
import student;         // 学生模块，继承自Person，包含学生特有属性和方法
import teacher;         // 教师模块，继承自Person，包含教师特有属性和方法
import Class;           // 课程模块，管理课程信息和学生、教师关系
import enrollment;      // 选课管理模块，处理学生选课业务逻辑
import arrangement;     // 排课管理模块，处理教师排课业务逻辑
import relationbroker;  // 关系代理基类，提供基础查找功能
import studentbroker;   // 学生代理类，专门处理学生查找逻辑
import teacherbroker;   // 教师代理类，专门处理教师查找逻辑

using std::string;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using std::cin;
using std::getline;
using std::make_shared;

export class UI {
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

    // 显示主菜单
    int showMainMenu() {
        std::print("========================================\n");
        std::print("      学生选课管理系统 - 主菜单\n");
        std::print("========================================\n");
        std::print(" 1. 创建学生\n");
        std::print(" 2. 创建教师\n");
        std::print(" 3. 创建课程\n");
        std::print(" 4. 学生选课\n");
        std::print(" 5. 安排教师授课\n");
        std::print(" 6. 查看所有学生\n");
        std::print(" 7. 查看所有教师\n");
        std::print(" 8. 查看所有课程\n");
        std::print(" 0. 退出系统\n");
        std::print("========================================\n");

        return getIntInput("请选择操作 (0-8): ");
    }

    // 创建学生
    void createStudent() {
        std::print("=== 创建学生 ===\n");

        string name = getStringInput("姓名: ");
        int age = getIntInput("年龄: ");
        string gender = getStringInput("性别(男/女): ");
        string sid = getStringInput("学号: ");

        try {
            // 检查学号是否已存在
            studentBroker broker;
            auto existing = broker.findStudentById(sid, system.getStudentList());
            if (existing) {
                std::print("学号 {} 已存在！\n", sid);
                pause();
                return;
            }

            // 创建学生对象
            auto stu = make_shared<Student>(name, age, gender, sid);

            // 添加到系统
            system.getStudentList().push_back(stu);

            std::print("\n学生创建成功！\n");
            std::print("姓名: {}, 学号: {}, 年龄: {}, 性别: {}\n",
                name, sid, age, gender);

        } catch (const std::exception& e) {
            std::print("创建失败: {}\n", e.what());
        } catch (...) {
            std::print("创建失败: 未知错误\n");
        }

        pause();
    }

    // 创建教师
    void createTeacher() {
        std::print("=== 创建教师 ===\n");

        string name = getStringInput("姓名: ");
        int age = getIntInput("年龄: ");
        string gender = getStringInput("性别(男/女): ");
        string tid = getStringInput("教师工号: ");

        try {
            // 检查工号是否已存在
            teacherBroker broker;
            auto existing = broker.findTeacherById(tid, system.getTeacherList());
            if (existing) {
                std::print("工号 {} 已存在！\n", tid);
                pause();
                return;
            }

            auto tea = make_shared<Teacher>(name, age, gender, tid);
            system.getTeacherList().push_back(tea);

            std::print("\n教师创建成功！\n");
            std::print("姓名: {}, 工号: {}, 年龄: {}, 性别: {}\n",
                name, tid, age, gender);

        } catch (const std::exception& e) {
            std::print("创建失败: {}\n", e.what());
        } catch (...) {
            std::print("创建失败: 未知错误\n");
        }

        pause();
    }

    // 创建课程
    void createCourse() {
        std::print("=== 创建课程 ===\n");

        string name = getStringInput("课程名称: ");
        string cid = getStringInput("课程编号: ");
        double credit = getDoubleInput("学分: ");

        try {
            // 检查课程编号是否已存在
            relationBroker broker;
            auto existing = broker.findCourseById(cid, system.getCourseList());
            if (existing) {
                std::print("课程编号 {} 已存在！\n", cid);
                pause();
                return;
            }

            auto course = make_shared<Class>(name, cid, credit);
            system.getCourseList().push_back(course);

            std::print("\n课程创建成功！\n");
            std::print("课程: {} ({}), 学分: {}\n", name, cid, credit);

        } catch (const std::exception& e) {
            std::print("创建失败: {}\n", e.what());
        } catch (...) {
            std::print("创建失败: 未知错误\n");
        }

        pause();
    }

    // 学生选课
    void studentEnrollCourse() {
        std::print("=== 学生选课 ===\n");

        // 检查是否有学生和课程
        if (system.getStudentList().empty()) {
            std::print("系统中没有学生，请先创建学生！\n");
            pause();
            return;
        }

        if (system.getCourseList().empty()) {
            std::print("系统中没有课程，请先创建课程！\n");
            pause();
            return;
        }

        // 显示学生列表
        std::print("学生列表:\n");
        for (size_t i = 0; i < system.getStudentList().size(); ++i) {
            auto stu = system.getStudentList()[i];
            std::print("{}. {} ({})\n", i+1, stu->getName(), stu->getStudentId());
        }

        // 显示课程列表
        std::print("\n课程列表:\n");
        for (size_t i = 0; i < system.getCourseList().size(); ++i) {
            auto course = system.getCourseList()[i];
            std::print("{}. 课程编号: {}\n", i+1, course->getid());
        }

        int stuIdx = getIntInput("\n请选择学生序号: ") - 1;
        int courseIdx = getIntInput("请选择课程序号: ") - 1;

        if (stuIdx >= 0 && stuIdx < static_cast<int>(system.getStudentList().size()) &&
            courseIdx >= 0 && courseIdx < static_cast<int>(system.getCourseList().size())) {

            string sid = system.getStudentList()[stuIdx]->getStudentId();
            string cid = system.getCourseList()[courseIdx]->getid();

            try {
                // 创建Enrollment实例
                auto& enrollmentInstance = Enrollment::singletonEnroll();
                enrollmentInstance.studentEnrollCourse(sid, cid);

                std::print("\n选课成功！\n");
                std::print("学生: {} 选择了课程: {}\n",
                    system.getStudentList()[stuIdx]->getName(), cid);

            } catch (const std::exception& e) {
                std::print("选课失败: {}\n", e.what());
            } catch (...) {
                std::print("选课失败: 未知错误\n");
            }
        } else {
            std::print("序号无效！\n");
        }

        pause();
    }

    // 安排教师授课
    void arrangeTeacherForCourse() {
        std::print("=== 安排教师授课 ===\n");

        if (system.getTeacherList().empty()) {
            std::print("系统中没有教师，请先创建教师！\n");
            pause();
            return;
        }

        if (system.getCourseList().empty()) {
            std::print("系统中没有课程，请先创建课程！\n");
            pause();
            return;
        }

        // 显示教师列表
        std::print("教师列表:\n");
        for (size_t i = 0; i < system.getTeacherList().size(); ++i) {
            auto tea = system.getTeacherList()[i];
            std::print("{}. {} ({})\n", i+1, tea->getName(), tea->getTeacherId());
        }

        // 显示课程列表
        std::print("\n课程列表:\n");
        for (size_t i = 0; i < system.getCourseList().size(); ++i) {
            auto course = system.getCourseList()[i];
            std::print("{}. 课程编号: {}\n", i+1, course->getid());
        }

        int teaIdx = getIntInput("\n请选择教师序号: ") - 1;
        int courseIdx = getIntInput("请选择课程序号: ") - 1;

        if (teaIdx >= 0 && teaIdx < static_cast<int>(system.getTeacherList().size()) &&
            courseIdx >= 0 && courseIdx < static_cast<int>(system.getCourseList().size())) {

            string tid = system.getTeacherList()[teaIdx]->getTeacherId();
            string cid = system.getCourseList()[courseIdx]->getid();

            try {
                // 创建Arrangement实例
                auto& arrangementInstance = Arrangement::singletonArrange();
                arrangementInstance.teacherArrangeCourse(tid, cid);

                std::print("\n安排成功！\n");
                std::print("教师: {} 安排了课程: {}\n",
                    system.getTeacherList()[teaIdx]->getName(), cid);

            } catch (const std::exception& e) {
                std::print("安排失败: {}\n", e.what());
            } catch (...) {
                std::print("安排失败: 未知错误\n");
            }
        } else {
            std::print("序号无效！\n");
        }

        pause();
    }

    // 查看所有学生
    void displayAllStudents() {
        std::print("=== 学生列表 ===\n");

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

    // 查看所有教师
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

    // 查看所有课程
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

    // 按学号查询学生
    void findStudentById() {
        std::print("=== 按学号查询学生 ===\n");
        string sid = getStringInput("请输入学号: ");

        studentBroker broker;
        auto student = broker.findStudentById(sid, system.getStudentList());

        if (student) {
            std::print("找到学生:\n");
            std::print("  姓名: {}\n", student->getName());
            std::print("  学号: {}\n", student->getStudentId());
            std::print("  年龄: {}\n", student->getAge());
            std::print("  性别: {}\n", student->getGender());
        } else {
            std::print("未找到学号为 {} 的学生\n", sid);
        }

        pause();
    }

    // 按工号查询教师
    void findTeacherById() {
        std::print("=== 按工号查询教师 ===\n");
        string tid = getStringInput("请输入教师工号: ");

        teacherBroker broker;
        auto teacher = broker.findTeacherById(tid, system.getTeacherList());

        if (teacher) {
            std::print("找到教师:\n");
            std::print("  姓名: {}\n", teacher->getName());
            std::print("  工号: {}\n", teacher->getTeacherId());
            std::print("  年龄: {}\n", teacher->getAge());
            std::print("  性别: {}\n", teacher->getGender());
        } else {
            std::print("未找到工号为 {} 的教师\n", tid);
        }

        pause();
    }

    // 按编号查询课程
    void findCourseById() {
        std::print("=== 按编号查询课程 ===\n");
        string cid = getStringInput("请输入课程编号: ");

        relationBroker broker;
        auto course = broker.findCourseById(cid, system.getCourseList());

        if (course) {
            std::print("找到课程:\n");
            std::print("  课程编号: {}\n", course->getid());
        } else {
            std::print("未找到课程编号为 {} 的课程\n", cid);
        }

        pause();
    }

public:
    // 构造函数
    UI() : system(System::singletonSystem()) {}

    // 运行UI主循环
    void run() {
        // 直接进入主菜单，不显示欢迎界面
        while (true) {
            int choice = showMainMenu();

            switch (choice) {
                case 1:  // 创建学生
                    createStudent();
                    break;
                case 2:  // 创建教师
                    createTeacher();
                    break;
                case 3:  // 创建课程
                    createCourse();
                    break;
                case 4:  // 学生选课
                    studentEnrollCourse();
                    break;
                case 5:  // 安排教师授课
                    arrangeTeacherForCourse();
                    break;
                case 6:  // 查看所有学生
                    displayAllStudents();
                    break;
                case 7:  // 查看所有教师
                    displayAllTeachers();
                    break;
                case 8:  // 查看所有课程
                    displayAllCourses();
                    break;
                case 0:  // 退出系统
                    std::print("感谢使用学生选课管理系统，再见！\n");
                    return;
                default:
                    std::print("无效选择，请重新输入！\n");
                    pause();
            }
        }
    }
};
