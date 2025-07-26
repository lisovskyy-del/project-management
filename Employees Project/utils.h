#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <ctime>


/*
1. Client      (id, name, phone)
2. Employee    (id, firstName, lastName, age, position)
3. Task        (id, name, desc, status, employeeId) ← without projectId for now
4. Project     (id, name, desc, clientId, taskId, timeStart, timeEnd)
*/

const std::string COLOR_RED = "\033[31m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_YELLOW = "\033[33m";
const std::string COLOR_RESET = "\033[0m";

namespace utils {
	const char DELIMITER = '|';

	bool validateString(const std::string& text);
	bool validateAge(int age);
	bool validateTimeStart(int timeStart);
	bool validateTimeEnd(int timeStart, int timeEnd);
	bool validatePhone(const std::string& phone);

	std::string currentDate();

	void printTableHeader(const std::vector<std::string>& headers);
	void printError(const std::string& message);
	void printSuccess(const std::string& message);

	std::vector<std::string> split(const std::string& text, char delimiter);
}

#endif