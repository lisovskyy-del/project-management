#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

struct Employee {
	int id;
	std::string firstName;
	std::string lastName;
	int age;
	std::string position;
	int taskId;
};

namespace employee {
	const std::string FILE_NAME = "employees.txt";

	void create(Employee& employee);
	void readAll(std::vector<Employee>& employees);
	void update(Employee& employee);
	void remove(int id);
	void searchByName(const std::vector<Employee>& employees, const std::string& name);
	void sortByAge(std::vector<Employee>& employees, bool ascending); // sorts age either by ascending or descending (user choice)
}

#endif