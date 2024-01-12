#pragma once
#include "IObserver.h"
#include "Messages.h"

#include <map>
#include <string>

class User : public IObserver {
  public:
    User();
    virtual ~User();

    bool update(const int event) override;

    void set_name(const std::string& name);
    void set_login(const std::string& login);
    void set_password(const std::string& password);
    void set_message(const std::string& message);
    void set_receiver(const std::string& receiver);

    const std::string& get_login() const { return login_; }
    const std::string& get_password() const { return password_; }

  private:
    std::string name_{};
    std::string login_{};
    std::string password_{};
    std::string message_{};
    std::string receiver_{};
    Messages<std::string>* messages_;
};
