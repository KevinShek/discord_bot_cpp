#include <fstream>
#include <iostream>
#include <dpp/dpp.h>

class ConnectionToBot {
public:
	ConnectionToBot() {
	}
	void joiner(const dpp::slashcommand_t& event);
	void leaver(const dpp::slashcommand_t& event);
};