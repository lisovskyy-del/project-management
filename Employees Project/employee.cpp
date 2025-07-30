#include "employee.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

namespace employee {
	void create(Employee& employee) {

		std::ofstream file(employee::FILE_NAME, std::ios::app);
		file << employee.id << "|" << employee.firstName << "|" 
			<< employee.lastName << "|" << employee.age << "|" << employee.position << "|" << employee.taskId << "\n";
		file.close();

		utils::printSuccess("Employee created.");
	}

	void readAll(std::vector<Employee>& employees) {
		employees.clear();
		std::ifstream file(employee::FILE_NAME);
		std::string line;

		while (std::getline(file, line)) {
			auto tokens = utils::split(line, utils::DELIMITER);
			if (tokens.size() == 6) {
				Employee employee = { std::stoi(tokens[0]), tokens[1], tokens[2], std::stoi(tokens[3]), tokens[4], std::stoi(tokens[5])};
				employees.push_back(employee);
			}
		}
	}

	void update(Employee& employee) {
		std::vector<Employee> employees;
		readAll(employees);

		bool isPresent = false;
		for (auto& e : employees) {
			if (e.id == employee.id) {
				isPresent = true;
				e = employee;
				break;
			}
		}

		if (isPresent) {
			std::ofstream file(employee::FILE_NAME);
			for (const auto& e : employees)
				file << e.id << "|" << e.firstName << "|" << e.lastName << "|" 
				<< e.age << "|" << e.position  << "|" << e.taskId << "\n";

			file.close();
			utils::printSuccess("Employee updated.");
		}
	}

	void remove(int id) {
		std::vector<Employee> employees;
		readAll(employees);

		employees.erase(std::remove_if(employees.begin(), employees.end(),
			[id](const Employee& e) { return e.id == id; }),
			employees.end());

		std::ofstream file(employee::FILE_NAME);
		for (const auto& e : employees)
			file << e.id << "|" << e.firstName << "|" << e.lastName << "|"
			<< e.age << "|" << e.position << "|" << e.taskId << "\n";

		file.close();
		utils::printSuccess("Employee deleted.");
	}

	void searchByName(const std::vector<Employee>& employees, const std::string& name) {
		utils::printTableHeader({ "\nID", "First Name", "Last Name", "Age", "Position", "Task ID"});
		for (const auto& employee : employees) {
			if (utils::toLower(employee.firstName).find(utils::toLower(name)) != std::string::npos ||
				utils::toLower(employee.lastName).find(utils::toLower(name)) != std::string::npos) {
				std::cout << std::left << std::setw(20) << employee.id << "|"
					<< std::setw(20) << employee.firstName << "|"
					<< std::setw(20) << employee.lastName << "|" 
					<< std::setw(20) << employee.age << "|" 
					<< std::setw(20) << employee.position << "|"
					<< std::setw(20) << employee.taskId << "|\n";
			}
		}
	}

	void sortByAge(std::vector<Employee>& employees, bool ascending) { // sorts age either by ascending or descending (user choice)
		std::sort(employees.begin(), employees.end(), [ascending](const Employee& a, const Employee& b) {
			return ascending ? a.age < b.age : a.age > b.age;
			});
		utils::printSuccess("Employees sorted.");
	}
}