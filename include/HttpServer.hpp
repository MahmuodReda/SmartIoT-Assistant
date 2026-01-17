#pragma once
#include <thread>
#include <atomic>

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
};
