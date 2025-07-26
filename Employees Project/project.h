#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>

struct Project {
	int id;
	std::string name;
	std::string description;
	int clientId;
	int taskId;
	int timeStart;
	int timeEnd;
};

namespace project {
	const std::string FILE_NAME = "project.txt";

	void create(Project& project);
	void readAll(std::vector<Project>& projects);
	void update(Project& project);
	void remove(int id);
	void searchByName(const std::vector<Project>& projects, const std::string& name);
	void searchProjectByClientId(const std::vector<Project>& projects, int clientId);
}

#endif