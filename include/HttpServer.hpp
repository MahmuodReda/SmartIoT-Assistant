#pragma once

#include <thread>
#include <atomic>
#include <httplib.h>

/**
 * @brief Simple HTTP server to receive JSON data from phone
 *        and write it to input.json
 */
class HttpServer
{
public:
    HttpServer();
    ~HttpServer();

    void start();
    void stop();

private:
    void run();

    std::thread serverThread;
    std::atomic<bool> running{false};
    httplib::Server server;
};
