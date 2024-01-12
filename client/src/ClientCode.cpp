#include "../headers/ClientCode.h"
#include "../headers/sha1.h"
#include "nlohmann/json.hpp"
#include <algorithm>
#include <exception>

void ClientCode::start() {
    std::cin.exceptions(std::istream::failbit);

    User* user = new User();
    bool flag = true;

    while(flag) {
        if(user->get_login().empty()) {
            std::cout << "\nNo current User";
        } else {
            std::cout << "\nThe current user: " << user->get_login() << std::endl;
        }
        std::cout << "\n\nSelect an action:" << std::endl;
        std::cout << "1 - registration, 2 - log in the chat,";
        std::cout << "\n3 - send messages, 4 - receive a message,";
        std::cout << "\n5 - exit the chat,  6 - quit from the program: ";
        char ch;
        std::cin >> ch;

        switch(ch) {
        case '1': {
            make_user(user);
            break;
        }
        case '2': {
            attach_user_toChat(user);
            break;
        }
        case '3': {
            if(!user->get_login().empty()) {
                send_messages_toServer(user);
            } else {
                std::cout << "\nUsers were not found!\nYou'll need to register in the chat!\n";
            }
            break;
        }
        case '4': {
            if(!user->get_login().empty()) {
                receive_messages_fromServer(user);
            } else {
                std::cout << "\nUsers were not found!\nYou'll need to register in the chat!\n";
            }
            break;
        }
        case '5': {
            if(!user->get_login().empty()) {
                detach_user_fromChat(user);
            } else {
                std::cout << "\nUsers were not found!\nYou'll need to register in the chat!\n";
            }
            break;
        }
        case '6': {
            if(user->update(6)) {
                // std::cout << "\nExit!" << std::endl;
                flag = false;
            } else {
                std::cout << "\nFailed! Try again." << std::endl;
            }
            break;
        }
        default: {
            std::cout << "\nTry again.";
            break;
        }
        }
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
    std::cout << "\nSee you soon again! " << std::endl;
    delete user;
}

void ClientCode::make_user(User* user) {
    try {
        std::string name;
        std::string login;
        std::string password;
        bool OnlyLettersNum = false;
        while(!OnlyLettersNum) {
            std::cout << "\nEnter only letters or numbers without using spaces or other symbols!\n";

            std::cout << "Enter your name: ";
            std::cin >> name;
            OnlyLettersNum = containsOnlyLettersNum(name);
            if(!OnlyLettersNum) {
                continue;
            }

            std::cout << "Enter your username: ";
            std::cin >> login;
            OnlyLettersNum = containsOnlyLettersNum(login);
            if(!OnlyLettersNum) {
                continue;
            }

            std::cout << "Enter your password: ";
            std::cin >> password;
            OnlyLettersNum = containsOnlyLettersNum(password);
            if(!OnlyLettersNum) {
                continue;
            }
        }
        password = sha1(password);
        user->set_name(name);
        user->set_login(login);
        user->set_password(password);

        if(!user->update(1)) {
            std::cout << "\nFailed! Try again." << std::endl;
            user->set_name("");
            user->set_login("");
            user->set_password("");
        }
    } catch(const std::istream::failure& ex) {
        std::cerr << "Failed to input: " << ex.what() << "\n";
    } catch(...) {
        std::cerr << "Some other exception\n";
    }
}

void ClientCode::attach_user_toChat(User* user) {
    std::cin.clear();
    std::cin.ignore(32767, '\n');

    try {
        std::string login;
        std::string password;
        bool OnlyLettersNum = false;
        while(!OnlyLettersNum) {
            std::cout << "\nEnter only letters or numbers without using spaces or other symbols!\n";

            std::cout << "Enter your login: ";
            std::cin >> login;
            OnlyLettersNum = containsOnlyLettersNum(login);
            if(!OnlyLettersNum) {
                continue;
            }

            std::cout << "Enter your password: ";
            std::cin >> password;
            OnlyLettersNum = containsOnlyLettersNum(password);
            if(!OnlyLettersNum) {
                continue;
            }
        }
        password = sha1(password);
        user->set_login(login);
        user->set_password(password);

        if(!user->update(2)) {
            std::cout << "\nFailed! Try again." << std::endl;
            user->set_login("");
            user->set_password("");
        }
    } catch(const std::istream::failure& ex) {
        std::cerr << "Failed to input: " << ex.what() << "\n";
    } catch(...) {
        std::cerr << "Some other exception\n";
    }
}

void ClientCode::send_messages_toServer(User* user) {
    std::string receiver;
    bool OnlyLettersNum = false;
    while(!OnlyLettersNum) {
        std::cout << "\nEnter only letters or numbers without using spaces or other "
                     "symbols!\n";
        std::cout << "\nSend to a user. Enter login : ";
        std::cin >> receiver;

        OnlyLettersNum = containsOnlyLettersNum(receiver);
        if(!OnlyLettersNum) {
            continue;
        }
    }
    std::string message;
    std::cout << "Enter your message: ";
    std::getline(std::cin >> std::ws, message);

    user->set_receiver(receiver);
    user->set_message(message);

    if(!user->update(3)) {
        std::cout << "\nFailed! Try again." << std::endl;
    }
}

void ClientCode::receive_messages_fromServer(User* user) {
    if(!user->update(4)) {
        std::cout << "\nFailed! Try again." << std::endl;
    }
}
void ClientCode::detach_user_fromChat(User* user) {
    if(user->update(5)) {
        std::cout << "\nyou are detached!" << std::endl;
        user->set_name("");
        user->set_login("");
        user->set_password("");
    } else {
        std::cout << "\nFailed! Try again." << std::endl;
    }
}

bool ClientCode::containsOnlyLettersNum(std::string const& str) {
    return std::all_of(str.begin(), str.end(), [](char const& c) { return std::isalnum(c); });
}
