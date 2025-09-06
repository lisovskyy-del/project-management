#include "utils.h"
#include "client.h"
#include "employee.h"
#include "task.h"
#include "project.h"
#include "report.h"
#include <iostream>
#include <iomanip>
#include <vector>

enum class MenuOption { // options are numbers. example: ADD_TASK = 12. if user inputs 12, option would be ADD_TASK.
	EXIT = 0,
	ADD_CLIENT, LIST_CLIENTS, UPDATE_CLIENT, DELETE_CLIENT, SEARCH_CLIENT,
	ADD_EMPLOYEE, LIST_EMPLOYEES, UPDATE_EMPLOYEE, DELETE_EMPLOYEE, SEARCH_EMPLOYEE, SORT_EMPLOYEES_BY_AGE,
	ADD_TASK, LIST_TASKS, UPDATE_TASK, DELETE_TASK, SEARCH_TASK, SEARCH_TASK_BY_STATUS,
	ADD_PROJECT, LIST_PROJECTS, UPDATE_PROJECT, DELETE_PROJECT, SEARCH_PROJECT, SEARCH_PROJECT_BY_CLIENT,
	GENERATE_REPORT, DEMO
};

void printMenu() {
	std::cout << COLOR_YELLOW << "\nProject Management System\n" << COLOR_RESET;
	std::cout << "0. Exit\n"
		<< "1. Add Client \n2. List Clients\n3. Update Client\n4. Delete Client\n5. Search Client\n\n"
		<< "6. Add Employee \n7. List Employees\n8. Update Employee\n9. Delete Employee\n10. Search Employee\n11. Sort Employees By Age\n\n"
		<< "12. Add Task\n13. List Tasks\n14. Update Task\n15. Delete Task\n16. Search Task\n17. Search Task By Status\n\n"
		<< "18. Add Project\n19. List Projects\n20. Update Project\n21. Delete Project\n22. Search Project\n23. Search Project By Client\n\n"
		<< "24. Generate Report\n25. Demo mode\n"
		<< "\nEnter Choice: ";
}

void demoMode() { // demo mode for quick test.
	Employee e1 = { 1, "Ivan", "Petrenko", 30, "Developer" };
	Employee e2 = { 2, "Olena", "Shevchenko", 28, "Designer" };
	employee::create(e1);
	employee::create(e2);

	Client c1 = { 1, "SoftGroup", "+380123456789"};
	client::create(c1);

	Project p1 = { 1, "Website Redesign", "Redesign client website", 1 };
	project::create(p1);

	Task t1 = { 1, "Create wireframes", "Initial UI mockups", TaskStatus::InProgress, 1, 1 };
	Task t2 = { 2, "Test landing page", "Functional testing", TaskStatus::NotStarted, 2, 1 };
	task::create(t1);
	task::create(t2);

	utils::printSuccess("Demo data created.\n\n");
}

int main() {
	std::vector<Client> clients;
	std::vector<Employee> employees;
	std::vector<Task> tasks;
	std::vector<Project> projects;

	while (true) {
		printMenu();
		int choice;
		std::cin >> choice;
		std::cin.ignore();

		switch (static_cast<MenuOption>(choice)) {
		case MenuOption::EXIT:
			return 0;
		case MenuOption::ADD_CLIENT: {
			Client client;
			std::cout << "\nEnter ID: ";
			std::cin >> client.id;
			std::cin.ignore();
			std::cout << "Enter name: ";
			std::getline(std::cin, client.name);
			std::cout << "Enter phone: ";
			std::getline(std::cin, client.phone);
			std::cout << "Enter project ID (-1 = no project): ";
			std::cin >> client.projectId;
			std::cin.ignore();

			if (utils::validateString(client.name) && utils::validatePhone(client.phone)) { // if validation is complete, create client.
				client::create(client);
			}
			else {
				utils::printError("Invalid input.\n");
			}
			break;
		}
		case MenuOption::LIST_CLIENTS: {
			client::readAll(clients);
			utils::printTableHeader({ "\nID", "Name", "Phone Number", "Project ID" }); // creates a fancy menu
			for (const auto& c : clients) {
				std::string name = c.name.length() > 20 ? c.name.substr(0, 17) + "..." : c.name; // check line 115 of task.cpp for explanation
				std::string phone = c.phone.length() > 20 ? c.phone.substr(0, 17) + "..." : c.phone;

				std::cout << std::left << std::setw(20) << c.id << "|"
					<< std::setw(20) << name << "|"
					<< std::setw(20) << phone << "|"
					<< std::setw(20) << c.projectId << "|\n";
			}
			break;
		}
		case MenuOption::UPDATE_CLIENT: {
			client::readAll(clients);

			int clientId;
			std::cout << "\nEnter ID to update client: ";
			std::cin >> clientId;

			auto it = std::find_if(clients.begin(), clients.end(), [clientId](const Client& c) { // if client id is found, continue.
				return c.id == clientId;
				});

			if (it != clients.end()) {
				Client updatedClient = *it;

				std::cin.ignore();
				std::cout << "\nEnter new ID: ";
				std::cin >> updatedClient.id;
				std::cin.ignore();
				std::cout << "Enter new name: ";
				std::getline(std::cin, updatedClient.name);

				std::cout << "Enter new phone number: ";
				std::getline(std::cin, updatedClient.phone);

				std::cout << "Enter new project ID (-1 = no project): ";
				std::cin >> updatedClient.projectId;

				client::update(updatedClient);
			}
			else {
				utils::printError("Client not found.\n");
			}
			break;
		}
		case MenuOption::DELETE_CLIENT: {
			client::readAll(clients);

			int clientId;
			std::cout << "\nEnter ID to delete client: ";
			std::cin >> clientId;

			auto it = std::find_if(clients.begin(), clients.end(), [clientId](const Client& c) {
				return c.id == clientId;
				});

			if (it != clients.end()) { // if client is found, remove.
				client::remove(clientId);
			}
			else {
				utils::printError("\nClient not found.");
			}
			break;
		}
		case MenuOption::SEARCH_CLIENT: {
			std::string name;
			std::cout << "\nEnter name to search: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			client::readAll(clients);
			client::searchByName(clients, name);
			break;
		}
		case MenuOption::ADD_EMPLOYEE: {
			Employee employee;
			std::cout << "\nEnter ID: ";
			std::cin >> employee.id;
			std::cin.ignore();
			std::cout << "Enter first name: ";
			std::getline(std::cin, employee.firstName);
			std::cout << "Enter last name: ";
			std::getline(std::cin, employee.lastName);
			std::cout << "Enter age: ";
			std::cin >> employee.age;
			std::cin.ignore();
			std::cout << "Enter position: ";
			std::getline(std::cin, employee.position);
			std::cout << "Enter task ID (-1 = no task): ";
			std::cin >> employee.taskId;
			std::cin.ignore();

			if (utils::validateString(employee.firstName) && utils::validateString(employee.lastName) && utils::validateAge(employee.age)) {
				employee::create(employee);
			}
			else {
				utils::printError("Invalid input.\n");
			}
			break;
		}
		case MenuOption::LIST_EMPLOYEES: {
			employee::readAll(employees);
			utils::printTableHeader({ "\nID", "First Name", "Last Name", "Age", "Position", "Task ID" });
			for (const auto& e : employees) {
				std::cout << std::left << std::setw(20) << e.id << "|"
					<< std::setw(20) << e.firstName << "|"
					<< std::setw(20) << e.lastName << "|"
					<< std::setw(20) << e.age << "|"
					<< std::setw(20) << e.position << "|"
					<< std::setw(20) << e.taskId << "|\n";
			}
			break;
		}
		case MenuOption::UPDATE_EMPLOYEE: {
			employee::readAll(employees);

			int employeeId;
			std::cout << "\nEnter ID to update employee: ";
			std::cin >> employeeId;

			auto it = std::find_if(employees.begin(), employees.end(), [employeeId](const Employee& e) {
				return e.id == employeeId;
				});

			if (it != employees.end()) {
				Employee updatedEmployee = *it;

				std::cin.ignore();
				std::cout << "\nEnter new ID: ";
				std::cin >> updatedEmployee.id;
				std::cin.ignore();
				std::cout << "Enter new First Name: ";
				std::getline(std::cin, updatedEmployee.firstName);

				std::cout << "Enter new Last Name: ";
				std::getline(std::cin, updatedEmployee.lastName);

				std::cout << "Enter new age: ";
				std::cin >> updatedEmployee.age;
				std::cin.ignore();

				std::cout << "Enter new position: ";
				std::getline(std::cin, updatedEmployee.position);

				std::cout << "Enter new task ID (-1 = no task): ";
				std::cin >> updatedEmployee.taskId;

				if (utils::validateString(updatedEmployee.firstName) && utils::validateString(updatedEmployee.lastName) && utils::validateAge(updatedEmployee.age)) {
					employee::update(updatedEmployee);
				}
				else {
					utils::printError("Invalid input.\n");
				}
			}
			else {
				utils::printError("Employee not found.\n");
			}
			break;
		}
		case MenuOption::DELETE_EMPLOYEE: {
			employee::readAll(employees);

			int employeeId;
			std::cout << "\nEnter ID to delete employee: ";
			std::cin >> employeeId;

			auto it = std::find_if(employees.begin(), employees.end(), [employeeId](const Employee& e) {
				return e.id == employeeId;
				});

			if (it != employees.end()) {
				employee::remove(employeeId);
			}
			else {
				utils::printError("\nEmployee not found.");
			}
			break;
		}
		case MenuOption::SEARCH_EMPLOYEE: {
			std::string name;

			std::cout << "\nEnter name to search: ";
			std::cin.ignore();
			std::getline(std::cin, name);

			employee::readAll(employees);
			employee::searchByName(employees, name);
			break;
		}
		case MenuOption::SORT_EMPLOYEES_BY_AGE: {
			employee::readAll(employees);

			std::cout << "Sort by ascending? (y-n): ";
			char ch;
			std::cin >> ch;

			if (ch == 'y' || ch == 'Y') {
				employee::sortByAge(employees, true);
				utils::printTableHeader({ "\nID", "First Name", "Last Name", "Age", "Position", "Task ID" });
				for (const auto& e : employees) {
					std::cout << std::left << std::setw(20) << e.id << "|"
						<< std::setw(20) << e.firstName << "|"
						<< std::setw(20) << e.lastName << "|"
						<< std::setw(20) << e.age << "|"
						<< std::setw(20) << e.position << "|"
						<< std::setw(20) << e.taskId << "|\n";
				}
			}
			else {
				employee::sortByAge(employees, false);
				utils::printTableHeader({ "\nID", "First Name", "Last Name", "Age", "Position", "Task ID" });
				for (const auto& e : employees) {
					std::cout << std::left << std::setw(20) << e.id << "|"
						<< std::setw(20) << e.firstName << "|"
						<< std::setw(20) << e.lastName << "|"
						<< std::setw(20) << e.age << "|"
						<< std::setw(20) << e.position << "|"
						<< std::setw(20) << e.taskId << "|\n";
				}
			}
			break;
		}
		case MenuOption::ADD_TASK: {
			Task task;

			std::cout << "\nEnter ID: ";
			std::cin >> task.id;
			std::cin.ignore();
			std::cout << "Enter name: ";
			std::getline(std::cin, task.name);
			std::cout << "Enter description: ";
			std::getline(std::cin, task.description);
			task.status = task::chooseStatus();
			std::cout << "Enter employee ID (-1 = no employee): ";
			std::cin >> task.employeeId;
			std::cout << "Enter project ID (-1 = no project): ";
			std::cin >> task.projectId;
			std::cin.ignore();

			task::create(task);

			break;
		}
		case MenuOption::LIST_TASKS: {
			task::readAll(tasks);
			utils::printTableHeader({ "\nID", "Name", "Description", "Status", "Employee ID", "Project ID" });
			for (const auto& task : tasks) {
				std::string name = task.name.length() > 20 ? task.name.substr(0, 17) + "..." : task.name;
				std::string description = task.description.length() > 20 ? task.description.substr(0, 17) + "..." : task.description;

				std::cout << std::left << std::setw(20) << task.id << "|"
					<< std::setw(20) << name << "|"
					<< std::setw(20) << description << "|"
					<< std::setw(20) << task::statusToString(task.status) << "|"
					<< std::setw(20) << task.employeeId << "|"
					<< std::setw(20) << task.projectId << "|\n";
			}
			break;
		}
		case MenuOption::UPDATE_TASK: {
			task::readAll(tasks);

			int taskId;
			std::cout << "\nEnter ID to update task: ";
			std::cin >> taskId;

			auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Task& t) {
				return t.id == taskId;
				});

			if (it != tasks.end()) {
				Task updatedTask = *it;

				std::cin.ignore();
				std::cout << "\nEnter new ID: ";
				std::cin >> updatedTask.id;
				std::cin.ignore();
				std::cout << "Enter new name: ";
				std::getline(std::cin, updatedTask.name);

				std::cout << "Enter new description: ";
				std::getline(std::cin, updatedTask.description);

				updatedTask.status = task::chooseStatus();

				std::cout << "Enter new employee ID: (-1 = no employee)";
				std::cin >> updatedTask.employeeId;

				std::cout << "Enter new project ID: (-1 = no project)";
				std::cin >> updatedTask.projectId;
				std::cin.ignore();

				task::update(updatedTask);
			}
			else {
				utils::printError("Task not found.\n");
			}
			break;
		}
		case MenuOption::DELETE_TASK: {
			task::readAll(tasks);

			int taskId;
			std::cout << "\nEnter ID to delete task: ";
			std::cin >> taskId;

			auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Task& t) {
				return t.id == taskId;
				});

			if (it != tasks.end()) {
				employee::remove(taskId);
			}
			else {
				utils::printError("\nTask not found.");
			}
			break;
		}
		case MenuOption::SEARCH_TASK: {
			std::string name;

			std::cout << "\nEnter name to search: ";
			std::cin.ignore();
			std::getline(std::cin, name);

			task::readAll(tasks);
			task::searchByName(tasks, name);
			break;
		}
		case MenuOption::SEARCH_TASK_BY_STATUS: {
			std::vector<Task> tasks;
			task::readAll(tasks);
			TaskStatus selected = task::chooseStatus();
			task::searchTaskByStatus(tasks, selected);
			break;
		}
		case MenuOption::ADD_PROJECT: {
			Project project;

			std::cout << "\nEnter ID: ";
			std::cin >> project.id;
			std::cin.ignore();
			std::cout << "Enter name: ";
			std::getline(std::cin, project.name);
			std::cout << "Enter description: ";
			std::getline(std::cin, project.description);
			std::cout << "Enter client ID (-1 = no client): ";
			std::cin >> project.clientId;
			std::cout << "Enter task ID (-1 = no task): ";
			std::cin >> project.taskId;
			std::cout << "Enter the start time of the project: ";
			std::cin >> project.timeStart;
			std::cout << "Enter the end time of the project: ";
			std::cin >> project.timeEnd;
			std::cin.ignore();

			if (utils::validateTimeStart(project.timeStart) && utils::validateTimeEnd(project.timeStart, project.timeEnd)) {
				project::create(project);
			}
			else {
				utils::printError("Invalid input.\n");
			}
			break;
		}
		case MenuOption::LIST_PROJECTS: {
			project::readAll(projects);
			utils::printTableHeader({ "\nID", "Name", "Description", "Client ID", "Task ID", "Time Start", "Time End" });
			for (const auto& project : projects) {
				std::string name = project.name.length() > 20 ? project.name.substr(0, 17) + "..." : project.name;
				std::string description = project.description.length() > 20 ? project.description.substr(0, 17) + "..." : project.description;

				std::cout << std::left << std::setw(20) << project.id << "|"
					<< std::setw(20) << name << "|"
					<< std::setw(20) << description << "|"
					<< std::setw(20) << project.clientId << "|"
					<< std::setw(20) << project.taskId << "|"
					<< std::setw(20) << project.timeStart << "|"
					<< std::setw(20) << project.timeEnd << "\n";
			}
			break;
		}
		case MenuOption::UPDATE_PROJECT: {
			project::readAll(projects);

			int projectId;
			std::cout << "Enter ID to update project: ";
			std::cin >> projectId;

			auto it = std::find_if(projects.begin(), projects.end(), [projectId](const Project& p) {
				return p.id == projectId;
				});

			if (it != projects.end()) {
				Project updatedProject = *it;

				std::cin.ignore();
				std::cout << "\nEnter new ID: ";
				std::cin >> updatedProject.id;
				std::cin.ignore();
				std::cout << "Enter new name: ";
				std::getline(std::cin, updatedProject.name);
				std::cout << "Enter new description: ";
				std::getline(std::cin, updatedProject.description);
				std::cout << "Enter new client ID (-1 = no client): ";
				std::cin >> updatedProject.clientId;
				std::cout << "Enter new task ID (-1 = no task): ";
				std::cin >> updatedProject.taskId;
				std::cout << "Enter new start time: ";
				std::cin >> updatedProject.timeStart;
				std::cout << "Enter new end time: ";
				std::cin >> updatedProject.timeEnd;

				if (utils::validateTimeStart(updatedProject.timeStart) && utils::validateTimeEnd(updatedProject.timeStart, updatedProject.timeEnd)) {
					project::update(updatedProject);
				}
				else {
					utils::printError("Invalid input.\n");
				}
			}
			else {
				utils::printError("Project not found.\n");
			}
			break;
		}
		case MenuOption::DELETE_PROJECT: {
			project::readAll(projects);

			int projectId;
			std::cout << "Enter ID to update project: ";
			std::cin >> projectId;

			auto it = std::find_if(projects.begin(), projects.end(), [projectId](const Project& p) {
				return p.id == projectId;
				});

			if (it != projects.end()) {
				client::remove(projectId);
			}
			else {
				utils::printError("\nProject not found.");
			}
			break;
		}
		case MenuOption::SEARCH_PROJECT: {
			std::string name;

			std::cout << "\nEnter name to search: ";
			std::cin.ignore();
			std::getline(std::cin, name);

			project::readAll(projects);
			project::searchByName(projects, name);
			break;
		}
		case MenuOption::SEARCH_PROJECT_BY_CLIENT: {
			project::readAll(projects);
			int clientId;
			std::cout << "Enter Client ID to search for a project: ";
			std::cin >> clientId;
			std::cin.ignore();

			project::searchProjectByClientId(projects, clientId);
			break;
		}
		case MenuOption::GENERATE_REPORT: {
			report::showEmployeeWorkload(employees, tasks);
			report::showProjectProgress(projects, tasks);
			break;
		}
		case MenuOption::DEMO: {
			demoMode();
			break;
		}
		default:
			utils::printError("Invalid option. Please try again.\n");
			break;
		}
	}
}