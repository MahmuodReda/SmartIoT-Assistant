#include "HttpServer.hpp"
#include <httplib.h>
#include <fstream>
#include <iostream>

HttpServer::HttpServer() {}

HttpServer::~HttpServer()
{
    stop();
}

void HttpServer::start()
{
    running = true;
    std::cout << "[HTTP] Starting server thread...\n";
    serverThread = std::thread(&HttpServer::run, this);
}

void HttpServer::stop()
{
    running = false;
    if (serverThread.joinable())
        serverThread.join();
}

void HttpServer::run()
{
    httplib::Server server;

    /*  ANY REQUEST (for debug) */
    server.set_logger([](const httplib::Request &req, const httplib::Response &res)
                      { std::cout << "[HTTP] Incoming request from "
                                  << req.remote_addr << " "
                                  << req.method << " "
                                  << req.path << "\n"; });

    /*  TEST ENDPOINT */
    server.Get("/ping", [](const httplib::Request &, httplib::Response &res)
               { res.set_content("Server is alive", "text/plain"); });

    /*  DATA ENDPOINT */
    server.Post("/data", [](const httplib::Request &req, httplib::Response &res)
                {
        std::cout << "[HTTP] /data endpoint HIT\n";
        std::cout << "[HTTP] Body size: " << req.body.size() << " bytes\n";

        if (req.body.empty())
        {
            res.status = 400;
            res.set_content("Empty body", "text/plain");
            return;
        }

        std::ofstream file("D:\\Mahmood_Reda\\SmartIoT-Assistant\\data\\input.json", std::ios::trunc);
        if (!file)
        {
            res.status = 500;
            res.set_content("Failed to open file", "text/plain");
            return;
        }

        file << req.body;
        file.close();

        std::cout << "[HTTP] JSON saved successfully\n";

        res.status = 200;
        res.set_content("OK", "text/plain"); });

    std::cout << "[HTTP] Server listening on ALL interfaces\n";
    std::cout << "[HTTP] http://0.0.0.0:8080\n";

    server.listen("0.0.0.0", 8080);
}
