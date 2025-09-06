#include "utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <regex>

namespace utils {
    bool validateString(const std::string& text) {
        return !text.empty() && std::all_of(text.begin(), text.end(), [](char c) -> bool {
            return std::isalpha(c) || c == ' ' || c == '-' || c == '\''; // return true if name is valid (valid name is Oleksandr, not O-lek-san-dr)
            });
    }

    bool validateAge(int age) {
        return age >= 18 && age <= 100; // if employee age > 18 and < 100, return true
    }

    bool validateTimeStart(int timeStart) {
        return timeStart >= 1800 && timeStart <= std::time(nullptr) / 31536000 + 1970; // if timestart < today's time, return true
    }

    bool validateTimeEnd(int timeStart, int timeEnd) {
        return timeEnd >= timeStart && timeEnd <= 2300; // if timestart < timeend and timeend < year 2300, return true
    }

    bool validatePhone(const std::string& phone) {
        std::regex pattern("\\+?\\d{10,12}");
        return std::regex_match(phone, pattern); // example: +12345678901
    }

    std::string utils::toLower(const std::string& str) { // lowers data's characters for easier reading
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return lowerStr;
    }

    void printTableHeader(const std::vector<std::string>& headers) { // will bring up a nice, cool-looking menu!
        for (auto& header : headers) {
            std::cout << std::left << std::setw(20) << header << "|";
        }
        std::cout << "\n" << std::string(headers.size() * 21, '-') << "\n";
    }

    void printError(const std::string& message) { // error message
        std::cout << COLOR_RED << "Error: " << message << COLOR_RESET << "\n";
    }

    void printSuccess(const std::string& message) { // success message
        std::cout << COLOR_GREEN << "Success: " << message << COLOR_RESET << "\n";
    }

    std::vector<std::string> split(const std::string& text, char delimiter) { // splits data to analyze
        std::vector<std::string> result;
        std::string token;
        for (auto c : text) {
            if (c == delimiter) { // if char is |, then push the token in vector, and continue reading
                result.push_back(token);
                token.clear();
            }
            else {
                token += c;
            }
        }
        if (!token.empty()) result.push_back(token);
        return result;
    }
}