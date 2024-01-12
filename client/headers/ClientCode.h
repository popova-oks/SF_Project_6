#pragma once
#include "User.h"
#include <iostream>

class ClientCode {
  public:
    void start();
    bool containsOnlyLettersNum(std::string const& str);
    void make_user(User* user);
    void attach_user_toChat(User* user);
    void send_messages_toServer(User* user);
    void receive_messages_fromServer(User* user);
    void detach_user_fromChat(User* user);
};