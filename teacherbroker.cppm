// Module   teacherBroker
// File: teacherbroker.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-17 15:06:02
// Description:老师类的查找模块，单独实现为一个类
//
export module gradesystem:teacherbroker;
import std;
import :relationbroker;
import :teacher;

using std::vector; using std::string;
using std::shared_ptr; using std::weak_ptr;
using std::print;

export class teacherBroker:public relationBroker
{
public:
    teacherBroker() = default;
    shared_ptr<Teacher> findTeacherById(string tid,vector<shared_ptr<Teacher>> teacherList);//查找老师ID
private:
};

shared_ptr<Teacher> teacherBroker::findTeacherById(string tid,vector<shared_ptr<Teacher>> teacherList)
{
    for(const auto& teaPtr : teacherList)
    {
        if(!teaPtr)
        {
            continue;
        }

        if(teaPtr->getTeacherId() == tid)
        {
            print("成功找到老师：ID={}\n",tid);
            return teaPtr;
        }
    }
    return nullptr;
}
