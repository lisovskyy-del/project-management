#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

struct Client {
	int id;
	std::string name;
	std::string phone;
	int projectId;
};

namespace client {
	const std::string FILE_NAME = "clients.txt";

	void create(Client& client);
	void readAll(std::vector<Client>& clients);
	void update(Client& client);
	void remove(int id);
	void searchByName(const std::vector<Client>& clients, const std::string& name);
}

#endif