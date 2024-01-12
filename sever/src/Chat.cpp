#include "../headers/Chat.h"
#include "../headers/jsonHandler.h"
#include <fstream>
#include <iostream>
#include <limits>

Chat::Chat() : path_Clients_{"./clients.json"}, path_Messages_{"./messages.json"} {}

Chat::~Chat() {
    //try {
        // Удаление файлов
        //std::filesystem::remove(path_Clients_);
        //std::filesystem::remove(path_Messages_);
        //std::cout << "File deleted successfully" << std::endl;
    //} catch(const std::exception& e) {
        //std::cerr << "Error deleting file: " << e.what() << std::endl;
    //}
    if(messages_ != nullptr) {
        delete messages_;
    }
}

void Chat::receive_message() {
    if(messages_ == nullptr) {
        messages_ = new Messages<std::string>();
    }
    messages_->get_messages(this);
}

nlohmann::json Chat::update(nlohmann::json& json) {
    nlohmann::json answ_json;
    if(json["key"] == "1") {
        std::string login = json["login"];
        std::string password = json["password"];
        if(is_checkClient(login, password)) {
            answ_json["message"] = "The client is already exited!";
        } else {
            add_newClient(json);
            answ_json = list_observers();
        }
    } else if(json["key"] == "2") {
        std::string login = json["login"];
        std::string password = json["password"];
        if(is_checkClient(login, password)) {
            isAutorized(login);
            answ_json = list_observers();
        } else {
            answ_json["message"] = "This client isn't exist!";
        }
    } else if(json["key"] == "3") {
        std::string login = json["sender"];
        add_newMessage(json);
        answ_json = list_messages(login);
    } else if(json["key"] == "4") {
        std::string login = json["login"];
        answ_json = list_messages(login);
    } else if(json["key"] == "5") {
        std::string login = json["login"];
        std::string password = json["password"];
        if(is_checkClient(login, password)) {
            notAutorized(login);
            answ_json = list_observers();
        } else {
            answ_json["message"] = "This client isn't exist!";
        }
    } else if(json["key"] == "exit") {
        answ_json["message"] = "The server is closed!";
    }
    return answ_json;
}

void Chat::add_newClient(const nlohmann::json& json) {
    nlohmann::json dateUsers;
    if(is_checkingFile(path_Clients_)) {
        dateUsers = readFile(path_Clients_);
    } else {
        // Если файл был пустой или его не существовало, создаем новый массив JSON
        dateUsers = nlohmann::json::array();
    }
    dateUsers.push_back(json);
    writeFile(path_Clients_, dateUsers);
}

void Chat::add_newMessage(const nlohmann::json& json) {
    nlohmann::json dateMessages;
    if(is_checkingFile(path_Messages_)) {
        dateMessages = readFile(path_Messages_);
    } else {
        // Если файл был пустой или его не существовало, создаем новый массив JSON
        dateMessages = nlohmann::json::array();
    }
    dateMessages.push_back(json);
    writeFile(path_Messages_, dateMessages);
}

nlohmann::json Chat::list_observers() {
    nlohmann::json dateUsers;
    if(is_checkingFile(path_Clients_)) {
        nlohmann::json json_data = readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["isAutorized"] == true) {
                    dateUsers.push_back(json_data[i]);
                }
            }
        } else {
            dateUsers["message"] = "No users!";
        }
    }
    return dateUsers;
}

nlohmann::json Chat::list_messages(const std::string& login) {
    nlohmann::json dateMessages;
    if(is_checkingFile(path_Messages_)) {
        nlohmann::json json_data = readFile(path_Messages_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["receiver"] == login.c_str()) {
                    dateMessages.push_back(json_data[i]);
                }
            }
        } else {
            dateMessages["message"] = "No messages!";
        }
    }
    return dateMessages;
}

bool Chat::is_checkClient(const std::string& login, const std::string& password) {
    bool is_check = false;
    if(is_checkingFile(path_Clients_)) {
        nlohmann::json json_data = readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["login"] == login && json_data[i]["password"] == password) {
                    is_check = true;
                    break;
                }
            }
        }
    }
    return is_check;
}

void Chat::isAutorized(const std::string& login) {
    nlohmann::json json_data;
    if(is_checkingFile(path_Clients_)) {
        json_data = readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["login"] == login) {
                    json_data[i]["isAutorized"] = true;
                }
            }
        }
    }
    writeFile(path_Clients_, json_data);
}

void Chat::notAutorized(const std::string& login) {
    nlohmann::json json_data;
    if(is_checkingFile(path_Clients_)) {
        json_data = readFile(path_Clients_);
        if(!json_data.empty()) {
            for(size_t i = 0; i < json_data.size(); i++) {
                if(json_data[i]["login"] == login) {
                    json_data[i]["isAutorized"] = false;
                }
            }
        }
    }
    writeFile(path_Clients_, json_data);
}