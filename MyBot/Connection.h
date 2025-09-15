#pragma once
#include <iostream>
class EnvLoader {
	std::string path = ".env";
public:
	EnvLoader() {
	}
	void load_env_file(const std::string& path);
	std::string get_env_var(const std::string& key);
};