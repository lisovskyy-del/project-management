#include "project.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

namespace project {
	void create(Project& project) {

		std::ofstream file(project::FILE_NAME, std::ios::app);
		file << project.id << "|" << project.name << "|"
			<< project.description << "|" << project.clientId << "|" << project.taskId << "|" 
			<< project.timeStart << "|" << project.timeEnd << "\n";
		file.close();

		utils::printSuccess("Project created.");
	}

	void readAll(std::vector<Project>& projects) {
		projects.clear();
		std::ifstream file(project::FILE_NAME);
		std::string line;

		while (std::getline(file, line)) {
			auto tokens = utils::split(line, utils::DELIMITER);
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
		for (auto& p : projects) {
			if (p.id == project.id) {
				isPresent = true;
				p = project;
				break;
			}
		}

		if (isPresent) {
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

		projects.erase(std::remove_if(projects.begin(), projects.end(),
			[id](const Project& p) { return p.id == id; }),
			projects.end());

		std::ofstream file(project::FILE_NAME);
		for (const auto& p : projects)
			file << p.id << "|" << p.name << "|" << p.description << "|"
			<< p.clientId << "|" << p.taskId << p.timeStart << "|" << p.timeEnd << "\n";

		file.close();
		utils::printSuccess("Project deleted.");
	}

	void searchByName(const std::vector<Project>& projects, const std::string& name) {
		utils::printTableHeader({ "ID", "Name", "Description", "Client ID", "Task ID", "Time Start", "Time End"});
		for (const auto& project : projects) {
			if (project.name.find(name) != std::string::npos) {
				std::cout << std::left << std::setw(20) << project.id << "|"
					<< std::setw(20) << project.name << "|"
					<< std::setw(20) << project.description << "|"
					<< std::setw(20) << project.clientId << "|"
					<< std::setw(20) << project.taskId << "|"
					<< std::setw(20) << project.timeStart << "|"
					<< std::setw(20) << project.timeEnd << "\n";
			}
		}
	}

	void searchProjectByClientId(const std::vector<Project>& projects, int clientId) {
		utils::printTableHeader({ "ID", "Name", "Description", "Client ID", "Task ID", "Time Start", "Time End" });
		for (const auto& project : projects) {
			if (project.clientId == clientId) {
				std::cout << std::left << std::setw(20) << project.id << "|"
					<< std::setw(20) << project.name << "|"
					<< std::setw(20) << project.description << "|"
					<< std::setw(20) << project.clientId << "|"
					<< std::setw(20) << project.taskId << "|"
					<< std::setw(20) << project.timeStart << "|"
					<< std::setw(20) << project.timeEnd << "\n";
			}
		}
	}
}