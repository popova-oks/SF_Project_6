cmake_minimum_required(VERSION 3.22.1) # Укажите версию CMake

project(Project_3) # Замените "MyProject" на имя вашего проекта

# Укажите исходные файлы вашего проекта
set(SOURCES
    src/main.cpp
    src/Chat.cpp
    src/ClientCode.cpp
    src/jsonHandler.cpp
    src/Messages.cpp
    src/sha1.cpp
    src/User.cpp
    src/ConnectionTCP.cpp
)

# Добавьте исполняемый файл
add_executable(main ${SOURCES})
target_compile_options(main PRIVATE -g -O0)


# Укажите дополнительные настройки и библиотеки, если необходимо
# target_link_libraries(my_app your_library)

# Укажите директории для поиска заголовочных файлов, если необходимо
# target_include_directories(my_app PUBLIC include)
include_directories(${CMAKE_SOURCE_DIR}/json/include)
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Установите параметры компиляции, если необходимо
# target_compile_options(my_app PRIVATE -Wall -Wextra)