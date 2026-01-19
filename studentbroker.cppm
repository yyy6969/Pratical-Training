// Module   studentbroker
// File: studentbroker.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 18:22:05
// Description:学生查找类，继承查找基类，对学生的id号进行查找判断该学生是否存在
//
export module gradesystem:studentbroker;
import std;
import :relationbroker;
import :student;

using std::vector; using std::string;
using std::shared_ptr; using std::weak_ptr;

export class studentBroker:public relationBroker
{
public:
    studentBroker() = default;
    shared_ptr<Student> findStudentById(string sid,vector<shared_ptr<Student>> studentlist);
private:

};

shared_ptr<Student> studentBroker::findStudentById(string sid,vector<shared_ptr<Student>> studentlist)
{
    for (const auto& stuPtr : studentlist)
    {
           // 空指针检查：避免访问空的Student对象
           if (!stuPtr) {
               continue;
           }

           // 对比学生ID
           if (stuPtr->getStudentId() == sid) {
               std::print("成功找到学生：ID={}\n", sid);
               return stuPtr;
           }
    }
    return nullptr;
}
