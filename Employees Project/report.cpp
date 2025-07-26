#include "report.h"
#include <iostream>
#include <iomanip>

namespace report {
	void showEmployeeWorkload(const std::vector<Employee>& employees, const std::vector<Task>& tasks) {
		for (const auto& employee : employees) {
			int total = 0;
			int completed = 0;
			for (const auto& task : tasks) {
				if (task.employeeId == employee.id) {
					total++;
					if (task.status == TaskStatus::Completed) completed++;
				}
			}
			std::cout << employee.firstName << " " << employee.lastName
				<< " - Total tasks: " << total
				<< ", Completed: " << completed
				<< ", Active: " << (total - completed) << "\n";
		}
	}

	void showProjectProgress(const std::vector<Project>& projects, const std::vector<Task>& tasks) {
		for (const auto& project : projects) {
			int total = 0;
			int completed = 0;
			for (const auto& task : tasks) {
				if (task.projectId == project.id) {
					total++;
					if (task.status == TaskStatus::Completed) completed++;
				}
			}
			double progress = total > 0 ? (completed * 100.0 / total) : 0;
			std::cout << project.name << " - Progress: "
				<< std::fixed << std::setprecision(2)
				<< progress << "%\n";
		}
	}
}