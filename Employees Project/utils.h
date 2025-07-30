#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <ctime>

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

	std::string toLower(const std::string& str);

	void printTableHeader(const std::vector<std::string>& headers);
	void printError(const std::string& message);
	void printSuccess(const std::string& message);


	std::vector<std::string> split(const std::string& text, char delimiter); // splits data to analyze
}

#endif