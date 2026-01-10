cmake_minimum_required(VERSION 3.16)

project(SmartIoT_Assistant LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(files
    main.cpp
    src/Communication.cpp
)

message(STATUS "SmartIoT files: ${files}")


add_executable(SmartIoT ${files})

target_include_directories(SmartIoT PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
