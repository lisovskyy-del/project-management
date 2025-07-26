#include "task.h"
#include "employee.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>

namespace task {
    TaskStatus chooseStatus() {
        int choice;
        std::cout << "\nChoose status: \n"
            << "1. Not Started\n" << "2. In Progress\n"
            << "3. Completed\n" << "4. On Hold\n"
            << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: return TaskStatus::NotStarted;
            case 2: return TaskStatus::InProgress;
            case 3: return TaskStatus::Completed;
            case 4: return TaskStatus::OnHold;
            default: std::cout << "Error. By Default: Not Started.\n";
                return TaskStatus::NotStarted;
        }
    }

    std::string statusToString(TaskStatus status) {
        switch (status) {
            case TaskStatus::NotStarted: return "Not Started";
            case TaskStatus::InProgress: return "In Progress";
            case TaskStatus::Completed:  return "Completed";
            case TaskStatus::OnHold:     return "On Hold";
            default: return "Unknown";
        }
    }

    TaskStatus stringToStatus(const std::string& statusStr) {
        if (statusStr == "Not Started") return TaskStatus::NotStarted;
        if (statusStr == "In Progress") return TaskStatus::InProgress;
        if (statusStr == "Completed")   return TaskStatus::Completed;
        if (statusStr == "On Hold")     return TaskStatus::OnHold;
        return TaskStatus::NotStarted;
    }

    void create(Task& task) {

        std::ofstream file(task::FILE_NAME, std::ios::app);
        file << task.id << "|" << task.name << "|"
            << task.description << "|" << statusToString(task.status) << "|"
            << task.employeeId << "|" << task.projectId << "\n";
        file.close();

        utils::printSuccess("Task created.");
    }
    
    void readAll(std::vector<Task>& tasks) {
        tasks.clear();
        std::ifstream file(task::FILE_NAME);
        std::string line;

        while (std::getline(file, line)) {
            auto tokens = utils::split(line, utils::DELIMITER);
            if (tokens.size() == 6) {
                Task task = { std::stoi(tokens[0]), tokens[1], tokens[2], stringToStatus(tokens[3]), std::stoi(tokens[4]), std::stoi(tokens[5])};
                tasks.push_back(task);
            }
        }
    }

    void update(Task& task) {
        std::vector<Task> tasks;
        readAll(tasks);

        bool isPresent = false;
        for (auto& t : tasks) {
            if (t.id == task.id) {
                isPresent = true;
                t = task;
                break;
            }
        }

        if (isPresent) {
            std::ofstream file(task::FILE_NAME);
            for (const auto& t : tasks)
                file << t.id << "|" << t.name << "|" << t.description << "|"
                << statusToString(t.status) << "|" << t.employeeId << "|" << t.projectId << "\n";

            file.close();
            utils::printSuccess("Task updated.");
        }
    }

    void remove(int id) {
        std::vector<Task> tasks;
        readAll(tasks);

        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
            [id](const Task& t) { return t.id == id; }),
            tasks.end());

        std::ofstream file(task::FILE_NAME);
        for (const auto& t : tasks)
            file << t.id << "|" << t.name << "|" << t.description << "|"
            << statusToString(t.status) << "|" << t.employeeId << "|" << t.projectId << "\n";

        file.close();
        utils::printSuccess("Task deleted.");
    }

    void searchByName(const std::vector<Task>& tasks, const std::string& name) {
        utils::printTableHeader({ "ID", "Name", "Description", "Status", "Employee ID", "Project ID"});
        for (const auto& task : tasks) {
            if (task.name.find(name) != std::string::npos) {
                std::cout << std::left << std::setw(20) << task.id << "|"
                    << std::setw(20) << task.name << "|"
                    << std::setw(20) << task.description << "|"
                    << std::setw(20) << statusToString(task.status) << "|"
                    << std::setw(20) << task.employeeId << "|"
                    << std::setw(20) << task.projectId << "|\n";
            }
        }
    }

    void searchTaskByStatus(const std::vector<Task>& tasks, TaskStatus selectedStatus) {
        utils::printTableHeader({ "ID", "Name", "Description", "Status", "Employee ID", "Project ID" });
        for (const auto& task : tasks) {
            if (task.status == selectedStatus) {
                std::cout << std::left << std::setw(20) << task.id << "|"
                    << std::setw(20) << task.name << "|"
                    << std::setw(20) << task.description << "|"
                    << std::setw(20) << statusToString(task.status) << "|"
                    << std::setw(20) << task.employeeId << "|"
                    << std::setw(20) << task.projectId << "|\n";
            }
        }
    }

    void assignTaskToEmployee(int employeeId, int taskId) {
        std::vector<Employee> employees;
        std::vector<Task> tasks;

        employee::readAll(employees);
        task::readAll(tasks);

        bool employeeExists = false;
        for (const auto& e : employees) {
            if (e.id == employeeId) {
                employeeExists = true;
                break;
            }
        }

        if (!employeeExists) {
            utils::printError("Employee not found.");
            return;
        }

        bool taskFound = false;
        for (auto& t : tasks) {
            if (t.id == taskId) {
                t.employeeId = employeeId;
                taskFound = true;
                break;
            }
        }

        if (!taskFound) {
            utils::printError("Task not found.");
            return;
        }

        std::ofstream file(task::FILE_NAME);
        for (const auto& t : tasks) {
            file << t.id << "|"
                << t.name << "|"
                << t.description << "|"
                << task::statusToString(t.status) << "|"
                << t.employeeId << "|"
                << t.projectId << "\n";
        }
        file.close();

        utils::printSuccess("Task assigned to employee.");
    }

    void assignProjectToTask(int taskId, int projectId) {
        std::vector<Task> tasks;
        task::readAll(tasks);

        bool found = false;
        for (auto& t : tasks) {
            if (t.id == taskId) {
                t.projectId = projectId;
                found = true;
                break;
            }
        }

        if (found) {
            std::ofstream file(task::FILE_NAME);
            for (const auto& t : tasks)
                file << t.id << "|" << t.name << "|" << t.description << "|"
                << statusToString(t.status) << "|" << t.employeeId << "|" << t.projectId << "\n";

            file.close();
            utils::printSuccess("Client attached to project.");
        }
        else {
            utils::printError("Client not found.");
        }
    }
}