#include "project.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

namespace project {
	void create(Project& project) { // writes data to the file.

		std::ofstream file(project::FILE_NAME, std::ios::app);
		file << project.id << "|" << project.name << "|"
			<< project.description << "|" << project.clientId << "|" << project.taskId << "|" 
			<< project.timeStart << "|" << project.timeEnd << "\n";
		file.close();

		utils::printSuccess("Project created.");
	}

	void readAll(std::vector<Project>& projects) { // reads data from a file.
		projects.clear();
		std::ifstream file(project::FILE_NAME);
		std::string line;

		while (std::getline(file, line)) {
			auto tokens = utils::split(line, utils::DELIMITER); // if target has 7 tokens (id,name, etc...), display data. otherwise, do not display.
			if (tokens.size() == 7) {
				Project employee = { std::stoi(tokens[0]), tokens[1], tokens[2], std::stoi(tokens[3]),
					 std::stoi(tokens[4]), std::stoi(tokens[5]), std::stoi(tokens[6])};
				projects.push_back(employee);
			}
		}
	}

	void update(Project& project) {
		std::vector<Project> projects;
		readAll(projects);

		bool isPresent = false;
		for (auto& p : projects) { // go through all projects
			if (p.id == project.id) { // If user id equals project id = continue.
				isPresent = true; 
				p = project;
				break;
			}
		}

		if (isPresent) { // if present is true, writes data to file.
			std::ofstream file(project::FILE_NAME);
			for (const auto& p : projects)
				file << p.id << "|" << p.name << "|" << p.description << "|"
				<< p.clientId << "|" << p.taskId << p.timeStart << "|" << p.timeEnd << "\n";

			file.close();
			utils::printSuccess("Project updated.");
		}
	}

	void remove(int id) { 
		std::vector<Project> projects;
		readAll(projects);

		projects.erase(std::remove_if(projects.begin(), projects.end(), // deletes all targets with the same id that user inputted.
			[id](const Project& p) { return p.id == id; }),
			projects.end());

		std::ofstream file(project::FILE_NAME); // after that, write all info into data.
		for (const auto& p : projects)
			file << p.id << "|" << p.name << "|" << p.description << "|"
			<< p.clientId << "|" << p.taskId << p.timeStart << "|" << p.timeEnd << "\n";

		file.close();
		utils::printSuccess("Project deleted.");
	}

	void searchByName(const std::vector<Project>& projects, const std::string& name) { // searches target by user input
		utils::printTableHeader({ "\nID", "Name", "Description", "Client ID", "Task ID", "Time Start", "Time End"});
		for (const auto& project : projects) {
			if (utils::toLower(project.name).find(utils::toLower(name)) != std::string::npos) { // lowers name and if found, continue.
				std::string name = project.name.length() > 20 ? project.name.substr(0, 17) + "..." : project.name; // check line 115 of task.cpp to see explanation.
				std::string description = project.description.length() > 20 ? project.description.substr(0, 17) + "..." : project.description;

				std::cout << std::left << std::setw(20) << project.id << "|"
					<< std::setw(20) << name << "|"
					<< std::setw(20) << description << "|"
					<< std::setw(20) << project.clientId << "|"
					<< std::setw(20) << project.taskId << "|"
					<< std::setw(20) << project.timeStart << "|"
					<< std::setw(20) << project.timeEnd << "\n";
			}
		}
	}

	void searchProjectByClientId(const std::vector<Project>& projects, int clientId) {
		utils::printTableHeader({ "\nID", "Name", "Description", "Client ID", "Task ID", "Time Start", "Time End" });
		for (const auto& project : projects) { // goes through all projects to see if they have same client id that user inputted. if there is one, call menu and display data.
			if (project.clientId == clientId) {
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
		}
	}
}