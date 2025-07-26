#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

enum class TaskStatus {
    NotStarted,
    InProgress,
    Completed,
    OnHold
};

struct Task {
    int id;
    std::string name;
    std::string description;
    TaskStatus status;
    int employeeId;
    int projectId;
};

namespace task {
    const std::string FILE_NAME = "tasks.txt";

    TaskStatus chooseStatus();
    std::string statusToString(TaskStatus status);
    TaskStatus stringToStatus(const std::string& statusStr);

    void create(Task& task);
    void readAll(std::vector<Task>& tasks);
    void update(Task& task);
    void remove(int id);
    void searchByName(const std::vector<Task>& tasks, const std::string& name);
    void searchTaskByStatus(const std::vector<Task>& tasks, TaskStatus selectedStatus);
}

#endif