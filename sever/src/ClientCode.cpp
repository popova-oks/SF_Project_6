#include "../headers/ClientCode.h"
#include <algorithm>
#include <exception>

void ClientCode::start() {
    Chat* chat = nullptr;
    try {
        chat = new Chat();
    } catch(const std::bad_alloc& ex) {
        std::cout << "Allocation failed: " << ex.what() << '\n';
    }
    chat->receive_message();
    std::cout << "\nSee you soon agan! " << std::endl;

    delete chat;
}