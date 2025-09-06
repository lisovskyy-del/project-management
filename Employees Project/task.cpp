#include "task.h"
#include "employee.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>

namespace task {
    TaskStatus chooseStatus() { // user has to choose status for task.
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

    std::string statusToString(TaskStatus status) { // reads status of the task and inputs status into string.
        switch (status) {
            case TaskStatus::NotStarted: return "Not Started";
            case TaskStatus::InProgress: return "In Progress";
            case TaskStatus::Completed:  return "Completed";
            case TaskStatus::OnHold:     return "On Hold";
            default: return "Unknown";
        }
    }

    TaskStatus stringToStatus(const std::string& statusStr) { // reads data from a string and returns status.
        if (statusStr == "Not Started") return TaskStatus::NotStarted;
        if (statusStr == "In Progress") return TaskStatus::InProgress;
        if (statusStr == "Completed")   return TaskStatus::Completed;
        if (statusStr == "On Hold")     return TaskStatus::OnHold;
        return TaskStatus::NotStarted;
    }

    void create(Task& task) { // writes data to the file.

        std::ofstream file(task::FILE_NAME, std::ios::app);
        file << task.id << "|" << task.name << "|"
            << task.description << "|" << statusToString(task.status) << "|"
            << task.employeeId << "|" << task.projectId << "\n";
        file.close();

        utils::printSuccess("Task created.");
    }
    
    void readAll(std::vector<Task>& tasks) { // reads data from a file.
        tasks.clear();
        std::ifstream file(task::FILE_NAME);
        std::string line;

        while (std::getline(file, line)) {
            auto tokens = utils::split(line, utils::DELIMITER); // if target has 6 tokens (id,name, etc...), display data. otherwise, do not display.
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
        for (auto& t : tasks) { // go through all tasks
            if (t.id == task.id) { // If user id equals task id = continue.
                isPresent = true;
                t = task;
                break;
            }
        }

        if (isPresent) { // if present is true, writes data to file.
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

        tasks.erase(std::remove_if(tasks.begin(), tasks.end(), // deletes all targets with the same id that user inputted.
            [id](const Task& t) { return t.id == id; }),
            tasks.end());

        std::ofstream file(task::FILE_NAME); // after that, write all info into data.
        for (const auto& t : tasks)
            file << t.id << "|" << t.name << "|" << t.description << "|"
            << statusToString(t.status) << "|" << t.employeeId << "|" << t.projectId << "\n";

        file.close();
        utils::printSuccess("Task deleted.");
    }

    void searchByName(const std::vector<Task>& tasks, const std::string& name) { // searches target by user input
        utils::printTableHeader({ "\nID", "Name", "Description", "Status", "Employee ID", "Project ID"});
        for (const auto& task : tasks) {
            if (utils::toLower(task.name).find(utils::toLower(name)) != std::string::npos) { // lowers name and if found, continue.
                std::string name = task.name.length() > 20 ? task.name.substr(0, 17) + "..." : task.name; // if task name is longer than 20 characters, shorten message to 17 characters and add "...". This is made because menu can get corrupted if name or desc is longer than 20 characters
                std::string description = task.description.length() > 20 ? task.description.substr(0, 17) + "..." : task.description;

                std::cout << std::left << std::setw(20) << task.id << "|"
                    << std::setw(20) << name << "|"
                    << std::setw(20) << description << "|"
                    << std::setw(20) << statusToString(task.status) << "|"
                    << std::setw(20) << task.employeeId << "|"
                    << std::setw(20) << task.projectId << "|\n";
            }
        }
    }

    void searchTaskByStatus(const std::vector<Task>& tasks, TaskStatus selectedStatus) { // searches target by user input
        utils::printTableHeader({ "\nID", "Name", "Description", "Status", "Employee ID", "Project ID" });
        for (const auto& task : tasks) {
            if (task.status == selectedStatus) { // lowers name and if found, continue.
                std::string name = task.name.length() > 20 ? task.name.substr(0, 17) + "..." : task.name;
                std::string description = task.description.length() > 20 ? task.description.substr(0, 17) + "..." : task.description;

                std::cout << std::left << std::setw(20) << task.id << "|"
                    << std::setw(20) << name << "|"
                    << std::setw(20) << description << "|"
                    << std::setw(20) << statusToString(task.status) << "|"
                    << std::setw(20) << task.employeeId << "|"
                    << std::setw(20) << task.projectId << "|\n";
            }
        }
    }
}