#pragma once
#include <fstream>
#include <iostream>
#include <dpp/dpp.h>

class JoinLeaveBot {
public:
	JoinLeaveBot() {
	}
	void joiner(const dpp::slashcommand_t& event);
	void leaver(const dpp::slashcommand_t& event);
};