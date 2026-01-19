import gradesystem;

import std;

int main() {
    try {
        // ========== 步骤1：获取UI单例实例 ==========
        // 和System/Arrangement等模块保持一致的单例调用方式
        auto& ui = UI::singletonUI();

        // ========== 步骤2：初始化系统（核心） ==========
        // 参数说明：数据库名、数据库用户名、数据库密码
        // 请根据你的PostgreSQL实际配置修改！
        // 例如：本地数据库名是gradeSystem，用户postgres，密码123456
        ui.initSystem("sqlDB", "yhr", "admin123");

        // ========== 步骤3：启动UI交互循环 ==========
        // 启动后进入控制台交互界面，直到用户选择0退出
        ui.run();

    } catch (const std::exception& e) {
        // 全局异常捕获：防止程序崩溃时无提示
        std::cerr << "\n程序异常退出：" << e.what() << "\n";
        return 1; // 异常退出，返回非0状态码
    }

    // 正常退出
    return 0;
}
