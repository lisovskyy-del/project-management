#ifndef REPORT_H
#define REPORT_H
#include <vector>
#include "employee.h"
#include "project.h"
#include "task.h"

namespace report {
	void showEmployeeWorkload(const std::vector<Employee>& employees, const std::vector<Task>& tasks);
	void showProjectProgress(const std::vector<Project>& projects, const std::vector<Task>& tasks);
}

#endif