cmake_minimum_required(VERSION 3.16)

project(SmartIoT_Assistant LANGUAGES CXX)

configure_file(
    ${CMAKE_SOURCE_DIR}/data/input.json
    ${CMAKE_BINARY_DIR}/data/input.json
    COPYONLY
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(files
    main.cpp
    src/Communication.cpp
    src/InputManager.cpp
    src/Scheduler.cpp
    src/Logic.cpp
    src/StateManager.cpp
)

message(STATUS "SmartIoT files: ${files}")


add_executable(SmartIoT ${files})

target_include_directories(SmartIoT PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(SmartIoT PRIVATE spdlog::spdlog_header_only)