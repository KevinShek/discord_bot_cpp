#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for _putenv
#include <sstream>
#include "Connection.h"

// Load .env and set environment variables
void EnvLoader::load_env_file(const std::string& path = ".env") {
    std::ifstream env_file(path);
    if (!env_file) {
        std::cerr << "Could not open .env file\n";
        return;
    }

    std::string line;
    while (std::getline(env_file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
            continue;

        // Parse key=value
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            // Construct string like "KEY=VALUE"
            std::string env_entry = key + "=" + value;
            // _putenv requires a writable C-string
            _putenv(_strdup(env_entry.c_str()));
        }
    }
}

std::string EnvLoader::get_env_var(const std::string& key) {
    char* buffer = nullptr;
    size_t size = 0;
    if (_dupenv_s(&buffer, &size, key.c_str()) == 0 && buffer != nullptr) {
        std::string result(buffer);
        free(buffer);
        return result;
    }
    return "";
}
