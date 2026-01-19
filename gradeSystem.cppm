export module gradesystem;
// 导出并导入所有子分区（顺序无关，建议按依赖顺序）
export import :person;
export import :course;
export import :student;
export import :teacher;
export import :relationbroker;
export import :studentbroker;
export import :teacherbroker;
export import :system;
export import :arrangement;
export import :enrollment;
export import :ui;
import std;
using std::print;
using std::shared_ptr;

// ----- 实现所有跨类交互函数（同一模块内，可访问私有成员） -----
void Teacher::teacherAddCourse(shared_ptr<Course> course)
{
    if (hasCourse()) {
        print("老师{}已分配课程{}，无法重复分配！\n", m_tid, m_teach_course->getName());
        return;
    }
    m_teach_course = course;
    print("老师{}成功分配课程{}\n", m_tid, course->getName());
}

void Student::studentAddCourse(shared_ptr<Course> cla)
{
    if (!cla) {
        print("【错误】学生{}（ID={}）：传入空课程对象，选课失败！\n",this->getName(), m_sid);
        return;
    }
    m_selected_courses.push_back(cla);
    print("学生{}（ID={}）成功选课程{}！\n", this->getName(), m_sid, cla->getName());
}
