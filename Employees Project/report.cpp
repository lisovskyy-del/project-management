#include "report.h"
#include <iostream>
#include <iomanip>

namespace report {
	void showEmployeeWorkload(const std::vector<Employee>& employees, const std::vector<Task>& tasks) { // statistics about all employees, all tasks (completed and active), all completed tasks, all active tasks.
		for (const auto& employee : employees) {
			int total = 0;
			int completed = 0;
			for (const auto& task : tasks) {
				if (task.employeeId == employee.id) {
					total++; // add 1 to total
					if (task.status == TaskStatus::Completed) completed++; // if status of the task is completed, add 1 to completed
				}
			}
			std::cout << employee.firstName << " " << employee.lastName
				<< " - Total tasks: " << total
				<< ", Completed: " << completed
				<< ", Active: " << (total - completed) << "\n";
		}
	}

	void showProjectProgress(const std::vector<Project>& projects, const std::vector<Task>& tasks) { // Shows general progress of project.
		for (const auto& project : projects) {
			int total = 0;
			int completed = 0;
			for (const auto& task : tasks) {
				if (task.projectId == project.id) {
					total++;
					if (task.status == TaskStatus::Completed) completed++;
				}
			}
			double progress = total > 0 ? (completed * 100.0 / total) : 0; // if total tasks are more than 0, do math and return general progress, else, return 0.
			std::cout << project.name << " - Progress: "
				<< std::fixed << std::setprecision(2)
				<< progress << "%\n";
		}
	}
}