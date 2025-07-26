#include "client.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

namespace client {
	void create(Client& client) {

		std::ofstream file(client::FILE_NAME, std::ios::app);
		file << client.id << "|" << client.name << "|" << client.phone << "|" << client.projectId << "\n";
		file.close();

		utils::printSuccess("Client created.");
	}

	void readAll(std::vector<Client>& clients) {
		clients.clear();
		std::ifstream file(client::FILE_NAME);
		std::string line;

		while (std::getline(file, line)) {
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
		for (auto& c : clients) {
			if (c.id == client.id) {
				isPresent = true;
				c = client;
				break;
			}
		}

		if (isPresent) {
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

		clients.erase(std::remove_if(clients.begin(), clients.end(),
			[id](const Client& c) { return c.id == id; }),
			clients.end());

		std::ofstream file(client::FILE_NAME);
		for (const auto& c : clients)
			file << c.id << "|" << c.name << "|" << c.phone << "|" << c.projectId << "\n";

		file.close();
		utils::printSuccess("Client deleted.");
	}

	void searchByName(const std::vector<Client>& clients, const std::string& name) {
		utils::printTableHeader({ "\nID", "Name", "Phone", "Project ID" });
		for (const auto& client : clients) {
			if (client.name.find(name) != std::string::npos) {
				std::cout << std::left << std::setw(20) << client.id << "|"
					<< std::setw(20) << client.name << "|"
					<< std::setw(20) << client.phone << "|"
					<< std::setw(20) << client.projectId << "|\n";
			}
		}
	}
}