import gradesystem;

import std;

int main() {
    try {
        //步骤1：获取UI单例实例
        auto& ui = UI::singletonUI();

        // 步骤2：初始化系统
        // 参数说明：数据库名、数据库用户名、数据库密码
        ui.initSystem("sqlDB", "yhr", "admin123");

        // 步骤3：启动UI交互循环
        ui.run();
        // 退出前清理内存
        auto& system = System::singletonSystem();
        system.getTeacherList().clear();
        system.getStudentList().clear();
        system.getCourseList().clear();

    } catch (const std::exception& e) {
        std::cerr << "\n程序异常退出：" << e.what() << "\n";
        return 1; // 异常退出，返回非0状态码
    }
    return 0;
}
