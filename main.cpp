#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
//四门课分别为 软件测试 软件项目管理 中间件 编译原理
class Student {
public:
    Student(){}
    Student(double software_testing,double software_project_management,double middleware,
            double compiling_principle, std::string name):software_testing(software_testing),
            software_project_management(software_project_management),middleware(middleware),
            compiling_principle(compiling_principle),name(name){}

    const double getAvgScore() const {
        return (software_testing+software_project_management+middleware+compiling_principle)/4.0;
    }

    const std::string& getName () const {
        return name;
    }
    friend bool operator<(const Student& student1, const Student& student2) {
        return student1.getAvgScore() > student2.getAvgScore();
    }

    const double& getSoftwareTesting() const {
        return software_testing;
    }

    const double& getSoftwareProjectManagement() const {
        return software_project_management;
    }

    const double& getMiddleware() const {
        return middleware;
    }

    const double& getCompilingPrinciple() const {
        return compiling_principle;
    }

private:
    double software_testing;
    double software_project_management;
    double middleware;
    double compiling_principle;
    std::string name;
};

void sortStudent(Student student[], const int sz) {
    std::sort(student, student + sz);

    std::cout << "student rank:" << std::endl;
    for (int i = 0; i < sz; ++i) {
        std::cout << student[i].getName() << std::endl;
    }
}

void setCourseAvg(double course_avg[], const int sz, const std::vector<Student>& student_list) {
    for (int i = 0; i < sz; ++i) {
        course_avg[0] += student_list[i].getSoftwareTesting() / 5;
        course_avg[1] += student_list[i].getSoftwareProjectManagement() / 5;
        course_avg[2] += student_list[i].getMiddleware() / 5;
        course_avg[3] += student_list[i].getCompilingPrinciple()/ 5;
    }

    for (int i = 0; i < 4; ++i) {
        std::cout << "the i-th course avg_score" << course_avg[i] << std::endl;
    }
}

void setFailStu(std::vector<Student>& fail_stu, const int sz, const std::vector<Student>& student_list) {
    for (int i = 0; i < sz; ++i) {
        int cnt = 0;
        if (student_list[i].getSoftwareTesting() < 60) {
            ++cnt;
        }
        if (student_list[i].getSoftwareProjectManagement() < 60) {
            ++cnt;
        }
        if (student_list[i].getMiddleware() < 60) {
            ++cnt;
        }
        if (student_list[i].getCompilingPrinciple() < 60) {
            ++cnt;
        }
        if(cnt >= 2) {
            fail_stu.push_back(student_list[i]);
        }
    }

    std::cout << "fail student:" << std::endl;
    for (auto& student : fail_stu) {
        std::cout << student.getName() << std::endl;
    }
}

inline bool checkFine(const double& score) {
    return score >= 85 && score <= 90;
}

void setFineStu(std::vector<Student>& fine_stu, const int sz, const std::vector<Student>& student_list) {
    for (int i = 0; i < sz; ++i) {
        if (checkFine(student_list[i].getAvgScore())) {
            fine_stu.push_back(student_list[i]);
        }
    }

    std::cout << "fine student:" << std::endl;
    for (auto& student : fine_stu) {
        std::cout << student.getName() << std::endl;
    }

}

inline bool checkScoreVaild(const double& score) {
    return score <= 100.0 && score >= 0.0;
}

const std::string studentnameprefix="student";

signed main() {
    std::vector<Student> student_list;
    std::vector<Student> fail_stu;
    std::vector<Student> fine_stu;
    double course_avg[4];
    Student stu_rank[5];

    //初始化成绩
    for (int i = 0; i < 5; ++i) {
        double software_testing;
        double software_project_management;
        double middleware;
        double compiling_principle;
        std::string studentname = studentnameprefix+(char)('1'+i);

        std::cout << "please input score for " << studentname << std::endl;
        std::cin >> software_testing >> software_project_management
                 >> middleware >> compiling_principle;

        assert(checkScoreVaild(software_testing) && checkScoreVaild(software_project_management)
        && checkScoreVaild(middleware) && checkScoreVaild(compiling_principle));

        Student student={software_testing, software_project_management,
                         middleware, compiling_principle, studentname};

        student_list.emplace_back(student);
        stu_rank[i] = student;
    }

    //求出所有课程平均值
    setCourseAvg(course_avg, 5, student_list);

    //对平均值排序
    sortStudent(stu_rank, 5);

    //求出挂科两门以上学生
    setFailStu(fail_stu, 5, student_list);

    //求出平均分数在85-90之间的学生
    setFineStu(fine_stu, 5, student_list);


    return 0;
}

/*
60 68 65 64
57 63 61 60
97 98 90 90
97 98 59 99
100 0 0 0
*/