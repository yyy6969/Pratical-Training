// Module enrollment
// File: enrollment.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 15:43:36
// Description:添加课程模块，用课程id号和学生id号进行匹配查找
//
export module enrollment;
import std;
import Class;
import student;
import studentbroker;

using std::string; using std::vector;

export class Enrollment
{
public:
    Enrollment(string c_id,string s_id);//全部用id来实现查找
private:
    string m_cid;//课程id
    string m_sid;//学生id
    vector<share_ptr<Student>> _studentlist;
    vector<share_ptr<Class>> _courselist;
};

