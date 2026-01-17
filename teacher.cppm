// Module teacher
// File: teacher.cpp   Version: 0.1.0   License: AGPLv3
// Created: YuHaoRan      2026-01-16 14:54:38
// Description:老师类，老师进行对课程的授课，其实相当于学生的选课
//
// Change Log:
//     [v0.1.1]  YuHaoRan   2026-01-17 18:11:04
//         * 添加了检验教师是否多选了所教课程函数，并且修改指针为一个class类的指针
export module teacher;
import std;
import person;

using std::string; using std::shared_ptr;
using std::vector;

export class Teacher:public Person
{
public:
    Teacher(string name,int age,string gender,string id);
    string getTeacherId() const;
    void addCourse(shared_ptr<class Class> course);

    int getTeachCourseId() const;// 新增：提取所教课程的ID（用于插入数据库）
    bool hasCourse() const;//新增：判断是否已分配课程（避免重复分配）

    ~Teacher() = default;
private:
    string m_tid;//老师id
    shared_ptr<Course> m_teach_course;// 核心：只存1门课（替代vector，贴合“只能教1门”的需求）
};

Teacher::Teacher(string name,int age,string gender,string id)
:Person(name,age,gender),m_tid(id),m_teach_course(nullptr)
{
    std::print("创建老师用户\n");
}

string Teacher::getTeacherId() const
{
    return m_tid;
}

void Teacher::addCourse(shared_ptr<class Class> course)
{
    if (m_teach_course != nullptr) {
            std::print("老师{}已分配课程【{}】，无法重复分配！\n",this->getName(), m_teach_course->getName());
            return;
        }
        // 正确拼写：push_back → 但这里直接赋值（因为只存1门课，无需vector）
        m_teach_course = course;
        std::print("老师{}分配授课课程：{}\n", getName(), course->getName());
}

int Teacher::getTeachCourseId() const
{
    // 如果未分配课程，返回-1（和数据库插入函数的默认值匹配）
    return (m_teach_course != nullptr) ? m_teach_course->getId() : -1;
}

bool Teacher::hasCourse() const
{
    return m_teach_course != nullptr;
}
