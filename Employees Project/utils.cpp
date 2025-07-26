#include "utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <regex>

namespace utils {
    bool validateString(const std::string& text) {
        return !text.empty() && std::all_of(text.begin(), text.end(), [](char c) -> bool {
            return std::isalpha(c) || c == ' ' || c == '-' || c == '\'';
            });
    }

    bool validateAge(int age) {
        return age >= 18 && age <= 100;
    }

    bool validateTimeStart(int timeStart) {
        return timeStart >= 1800 && timeStart <= std::time(nullptr) / 31536000 + 1970;
    }

    bool validateTimeEnd(int timeStart, int timeEnd) {
        return timeEnd >= timeStart && timeEnd <= 2300;
    }

    bool validatePhone(const std::string& phone) {
        std::regex pattern("\\+?\\d{10,12}");
        return std::regex_match(phone, pattern);
    }

    std::string currentDate() {
        std::time_t now = std::time(nullptr);
        std::tm timeStruct{};
        localtime_s(&timeStruct, &now);
        char buf[11];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", &timeStruct);
        return buf;
    }

    void printTableHeader(const std::vector<std::string>& headers) {
        for (auto& header : headers) {
            std::cout << std::left << std::setw(20) << header << "|";
        }
        std::cout << "\n" << std::string(headers.size() * 21, '-') << "\n";
    }

    void printError(const std::string& message) {
        std::cout << COLOR_RED << "Error: " << message << COLOR_RESET << "\n";
    }

    void printSuccess(const std::string& message) {
        std::cout << COLOR_GREEN << "Success: " << message << COLOR_RESET << "\n";
    }

    std::vector<std::string> split(const std::string& text, char delimiter) {
        std::vector<std::string> result;
        std::string token;
        for (auto c : text) {
            if (c == delimiter) {
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