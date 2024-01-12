#pragma once
#include "ISubject.h"
#include "Messages.h"

class Chat : public ISubject {
  public:
    Chat();
    virtual ~Chat();
    void receive_message();
    nlohmann::json update(nlohmann::json &json) override;

    void add_newClient(const nlohmann::json &json);
    void add_newMessage(const nlohmann::json &json);
    nlohmann::json list_observers();
    nlohmann::json list_messages(const std::string &login);
    
  private:  
    std::string path_Clients_;
    std::string path_Messages_;
    Messages<std::string>* messages_ = nullptr;

    bool is_checkClient(const std::string& login, const std::string& password);
    void isAutorized(const std::string& login);
    void notAutorized(const std::string& login);
};
