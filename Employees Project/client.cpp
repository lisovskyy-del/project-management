#include "client.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

namespace client {
	void create(Client& client) { // writes data to the file.

		std::ofstream file(client::FILE_NAME, std::ios::app);
		file << client.id << "|" << client.name << "|" << client.phone << "|" << client.projectId << "\n";
		file.close();

		utils::printSuccess("Client created.");
	}

	void readAll(std::vector<Client>& clients) { // reads data from a file.
		clients.clear();
		std::ifstream file(client::FILE_NAME);
		std::string line;

		while (std::getline(file, line)) { // if target has 4 tokens (id,name, etc...), display data. otherwise, do not display.
			auto tokens = utils::split(line, utils::DELIMITER);
			if (tokens.size() == 4) {
				Client client = { std::stoi(tokens[0]), tokens[1], tokens[2], std::stoi(tokens[3])};
				clients.push_back(client);
			}
		}
	}

	void update(Client& client) {
		std::vector<Client> clients;
		readAll(clients);

		bool isPresent = false;
		for (auto& c : clients) { // go through all clients
			if (c.id == client.id) { // If user id equals client id = continue.
				isPresent = true;
				c = client;
				break;
			}
		}

		if (isPresent) { // if present is true, writes data to file.
			std::ofstream file(client::FILE_NAME);
			for (const auto& c : clients)
				file << c.id << "|" << c.name << "|" << c.phone << "|" << c.projectId << "\n";

			file.close();
			utils::printSuccess("Client updated.");
		}
	}

	void remove(int id) {
		std::vector<Client> clients;
		readAll(clients);

		clients.erase(std::remove_if(clients.begin(), clients.end(), // deletes all targets with the same id that user inputted.
			[id](const Client& c) { return c.id == id; }),
			clients.end());

		std::ofstream file(client::FILE_NAME); // after that, write all info into data.
		for (const auto& c : clients)
			file << c.id << "|" << c.name << "|" << c.phone << "|" << c.projectId << "\n";

		file.close();
		utils::printSuccess("Client deleted.");
	}

	void searchByName(const std::vector<Client>& clients, const std::string& name) { // searches target by user input
		utils::printTableHeader({ "\nID", "Name", "Phone", "Project ID" });
		for (const auto& client : clients) {
			if (utils::toLower(client.name).find(utils::toLower(name)) != std::string::npos) { // lowers name and if found, continue.
				std::string name = client.name.length() > 20 ? client.name.substr(0, 17) + "..." : client.name;
				std::string phone = client.phone.length() > 20 ? client.phone.substr(0, 17) + "..." : client.phone;

				std::cout << std::left << std::setw(20) << client.id << "|"
					<< std::setw(20) << name << "|"
					<< std::setw(20) << phone << "|"
					<< std::setw(20) << client.projectId << "|\n";
			}
		}
	}
}