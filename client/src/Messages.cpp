#include "../headers/Messages.h"
#include "../headers/ConnectionTCP.h"
#include <fstream>
#include <iostream>
 
template <typename T> Messages<T>::~Messages() {
}

template <typename T> nlohmann::json Messages<T>::send_message(const nlohmann::json& json) {
    // преобразование JSON в строку
    std::string json_str_message = json.dump();
    // преобразуем строку в байты
    const char* message = json_str_message.c_str();
    // открываем сокет клиента, создаем соединение с сервером
    TCP_Client::processMessage();
    // передача сообщения через сокет
    ssize_t bytes = send(TCP_Client::socket_file_descriptor, message, strlen(message), 0);

    nlohmann::json answer_from_server;
    // если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0) {
        std::cout << "\nData send to the server successfully!" << std::endl;
        // очищаем буфер обмена клиента
        bzero(TCP_Client::buff, sizeof(TCP_Client::buff));
        // Ждем ответа от сервера
        recv(TCP_Client::socket_file_descriptor, TCP_Client::buff, sizeof(TCP_Client::buff), 0);
        answer_from_server = nlohmann::json::parse(TCP_Client::buff);
    } else {
        std::cout << "Data sending to the server failed!" << std::endl;
    }
    // очищаем буфер обмена клиента
    bzero(TCP_Client::buff, sizeof(TCP_Client::buff));
    //закрываем сокет, завершаем соединение
    close(TCP_Client::socket_file_descriptor);
    return answer_from_server;
}

template class Messages<std::string>;