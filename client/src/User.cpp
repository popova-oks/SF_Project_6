#include "../headers/User.h"
#include "nlohmann/json.hpp"
#include <iostream>

User::User() { messages_ = new Messages<std::string>(); }

User::~User() {
    delete messages_;
    messages_ = nullptr;
}

bool User::update(const int event) {
    nlohmann::json mess_toServer;
    nlohmann::json mess_fromServer;
    if(event == 1) {
        mess_toServer["key"] = "1";
        mess_toServer["name"] = name_;
        mess_toServer["login"] = login_;
        mess_toServer["password"] = password_;
        mess_toServer["isAutorized"] = true;
    } else if(event == 2) {
        mess_toServer["key"] = "2";
        mess_toServer["login"] = login_;
        mess_toServer["password"] = password_;
    } else if(event == 3) {
        mess_toServer["key"] = "3";
        mess_toServer["sender"] = login_;
        mess_toServer["password"] = password_;
        mess_toServer["receiver"] = receiver_;
        mess_toServer["message"] = message_;
    } else if(event == 4) {
        mess_toServer["key"] = "4";
        mess_toServer["login"] = login_;
        mess_toServer["password"] = password_;
    } else if(event == 5) {
        mess_toServer["key"] = "5";
        mess_toServer["login"] = login_;
        mess_toServer["password"] = password_;
    } else if(event == 6) {
        mess_toServer["key"] = "exit";
    }
    if(messages_ != nullptr) {
        mess_fromServer = messages_->send_message(mess_toServer);
    }

    std::string curr_user = {};
    if(event == 1 || event == 2) {
        std::cout << "Attached users: ";
        if(!mess_fromServer.empty()) {
            for(const auto& item : mess_fromServer) {
                if(item.find("login") != item.end()) {
                    std::cout << item["login"] << ",\t";
                    if(item["login"] == login_ && item["password"] == password_) {
                        curr_user = item["login"];
                    }
                } 
            }
            if(mess_fromServer.find("message") != mess_fromServer.end()) {
                std::cout << mess_fromServer["message"] << std::endl;
            }
        }
        if(curr_user.empty()) {
            return false;
        } else {
            return true;
        }
    } else if(event == 3 || event == 4) {
        if(!mess_fromServer.empty()) {
            std::cout << "Your messages: " << std::endl;
            for(const auto& item : mess_fromServer) {
                if(item.find("receiver") != item.end() && item["receiver"] == login_) {
                    std::cout << "Message: " << item["message"] << "\tfrom: " << item["sender"] << std::endl;
                }
            }
            if(mess_fromServer.find("message") != mess_fromServer.end()) {
                std::cout << mess_fromServer["message"] << std::endl;
            }
            return true;
        } else {
            std::cout << "No message" << std::endl;
            return false;
        }
    } else if(event == 5) {
        std::cout << "Attached users: ";
        if(!mess_fromServer.empty()) {
            for(const auto& item : mess_fromServer) {
                if(item.find("login") != item.end()) {
                    std::cout << item["login"] << ",\t";
                    if(item["login"] == login_ && item["password"] == password_) {
                        curr_user = item["login"];
                    }
                }
            }
            if(mess_fromServer.find("message") != mess_fromServer.end()) {
                std::cout << mess_fromServer["message"] << std::endl;
            }
        }
        if(curr_user.empty()) {
            std::cout << "You are detached!" << std::endl;
            return true;
        } else {
            return false;
        }
    } else if(event == 6) {
        if(!mess_fromServer.empty()) {
            if(mess_fromServer.find("message") != mess_fromServer.end()) {
                std::cout << mess_fromServer["message"] << std::endl;
            }
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void User::set_name(const std::string& name) {
    name_.clear();
    name_ = name;
}
void User::set_login(const std::string& login) {
    login_.clear();
    login_ = login;
}
void User::set_password(const std::string& password) {
    password_.clear();
    password_ = password;
}
void User::set_message(const std::string& message) {
    message_.clear();
    message_ = message;
}
void User::set_receiver(const std::string& receiver) {
    receiver_.clear();
    receiver_ = receiver;
}