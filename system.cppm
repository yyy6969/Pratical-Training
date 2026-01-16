// Module System
// File: system.cpp   Version: 0.1.0   License: AGPLv3
// Created:  YuHaoRan     2026-01-16 14:53:08
// Description:系统类，相当于管理人员，负责程序的一切执行
//

export module system;
import std;
import student;
import teacher;
import Class;

using std::string; using std::vector;
using std::shared_ptr; using std::weak_ptr;

export class System
{
public:
    System();
    static System& singleton();
    void exec();//程序执行函数，所有操作放在这里面
private:
};
