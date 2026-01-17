// Module   relationbroker
// File: relationbroker.cpp   Version: 0.1.0   License: AGPLv3
// Created:  YuHaoRan     2026-01-16 18:12:10
// Description:查找类基类，对要进行操作的学生类或者老师类进行查找
//
// Change Log:
//     [v0.1.1]  YuHaoRan   2026-01-17 14:19:10
//         * 添加了findCourseById这个两个broker都能使用的函数，放在他们的基类。
export module relationbroker;
import std;
import Class;

using std::shared_ptr; using std::vector;
using std::string;

export class relationBroker
{
public:
    relationBroker();
    shared_ptr<Class> findCourseById(string cid,vector<shared_ptr<Class>> courseList);//studen
private:
};

relationBroker::relationBroker()
{}

shared_ptr<Class> relationBroker::findCourseById(string cid,vector<shared_ptr<Class>>courseList)
{
    for(const auto& claPtr : courseList)
    {
        if(!claPtr)
        {
            continue;
        }

        if(claPtr->getid() == cid)
        {
            return claPtr;
        }
    }
}
