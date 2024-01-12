#include "../headers/jsonHandler.h"
#include <fstream>
#include <iostream>

bool is_checkingFile(const std::string& file_path) {
    std::ifstream input_file(file_path);
    if(!input_file.is_open()) {
        return false;
    }
    input_file.seekg(0, std::ios::end);     // Перемещаем указатель чтения в конец файла
    if(input_file.tellg() == 0) {           //если файл пустой
        input_file.close();
        return false;
    }
    return true;
}

nlohmann::json readFile(const std::string& file_path) {
    std::ifstream input_file(file_path);
    input_file.seekg(0, std::ios::beg);  // Возвращаем указатель чтения в начало файла
    nlohmann::json json_data;
    input_file >> json_data;
    input_file.close();
    return json_data;
}

bool writeFile(const std::string& file_path, nlohmann::json& json_data) {
    std::ofstream output_file(file_path, std::ios::out);
    if(!output_file.is_open()) {
        std::cout << "The json file isn't open!" << std::endl;
        return false;
    }
    output_file << std::setw(4) << json_data;
    output_file.close();
    return true;
}
