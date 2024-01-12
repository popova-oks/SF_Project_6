#include "../headers/Messages.h"
#include "../headers/ConnectionTCP.h"

template <typename T> void Messages<T>::get_messages(ISubject* chat) {
    // Communication Establishment
    TCP_Server::processRequest();
    bool flag = true;
    nlohmann::json json;
    nlohmann::json answ_json;

    while(flag) {
        TCP_Server::connection = accept(TCP_Server::socket_file_descriptor,
                                        (struct sockaddr*)&TCP_Server::client, &TCP_Server::length);
        if(TCP_Server::connection == -1) {
            std::cout << "Server is unable to accept the data from client.!" << std::endl;
        } else {
            // создаем поток, который будет обрабатывать данные от клиента

            // очищаем буфер сервера
            bzero(TCP_Server::buff, MESSAGE_LENGTH);
            // получаем сообщение от клиента
            ssize_t bytes =
                recv(TCP_Server::connection, TCP_Server::buff, sizeof(TCP_Server::buff), 0);
            if(TCP_Server::buff != nullptr) {
                if(bytes < 0) {
                    answ_json["message"] = "Error receiving data from client!";
                } else if(bytes >= 0) {
                    json = nlohmann::json::parse(TCP_Server::buff);
                    if(!json.is_null()) {
                        if(json["key"] == "exit") {
                            flag = false;
                        }
                        answ_json = chat->update(json);
                    }
                }
                // отправляем ответ клиенту
                std::string answ_str_message;
                if(answ_json.is_null()) {
                    answ_json["message"] = "It's no answer from server! Try again.";
                }
                answ_str_message = answ_json.dump();
                bytes = -1;
                bytes = send(TCP_Server::connection, answ_str_message.c_str(),
                             answ_str_message.size(), 0);
                // Если передали >= 0  байт, значит пересылка прошла успешно
                if(bytes >= 0) {
                    std::cout << "Data successfully sent to the client!" << std::endl;
                } else {
                    std::cout << "Data sending to the client failed!" << std::endl;
                }
            }
        }
        // очищаем буфер сервера
        bzero(TCP_Server::buff, MESSAGE_LENGTH);
    }
    // очищает (устанавливает в нули) буфер message размером MESSAGE_LENGTH
    bzero(TCP_Server::buff, MESSAGE_LENGTH);
    // закрываем сокет, завершаем соединение
    close(TCP_Server::socket_file_descriptor);
}
template class Messages<std::string>;