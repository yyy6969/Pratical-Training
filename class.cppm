export module Class;
import std;

using std::string; using std::vector;
using std::weak_ptr;


export class Class
{
public:
    Class(string csName,string csId,double credit);
private:
    string m_courseName;
    string m_courseId;
    double m_credit;
    static int cm_totalCount;//静态数据，整个类共享，统计课的数量
    vector<weak_ptr<class Student>> _student;
};

int Class::cm_totalCount = 0;//课程数目初始化为零

Class::Class(string csName,string csId,double credit)
:m_courseName(csName),m_courseId(csId),m_credit(credit)
{
    cm_totalCount++;//课程数量加一
}
