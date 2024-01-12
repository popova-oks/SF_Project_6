#pragma once
#include "nlohmann/json.hpp"
#include <string>

using json = nlohmann::json;

nlohmann::json readFile (const std::string& file_path);
bool writeFile (const std::string& file_path, nlohmann::json &json_data);
bool is_checkingFile (const std::string& file_path);