#include "HttpServer.hpp"
#include <fstream>
#include <iostream>

HttpServer::HttpServer() {}

HttpServer::~HttpServer()
{
    stop();
}

void HttpServer::start()
{
    if (running)
        return;

    running = true;
    std::cout << "[HTTP] Starting server thread...\n";
    serverThread = std::thread(&HttpServer::run, this);
}

void HttpServer::stop()
{
    if (!running)
        return;

    std::cout << "[HTTP] Stopping server...\n";
    running = false;

    // This will unblock server.listen()
    server.stop();

    if (serverThread.joinable())
        serverThread.join();

    std::cout << "[HTTP] Server stopped\n";
}

void HttpServer::run()
{
    /* Log every incoming request */
    server.set_logger([](const httplib::Request &req, const httplib::Response &)
                      { std::cout << "[HTTP] Incoming request from "
                                  << req.remote_addr << " "
                                  << req.method << " "
                                  << req.path << "\n"; });

    /* Health check endpoint */
    server.Get("/ping", [](const httplib::Request &, httplib::Response &res)
               { res.set_content("Server is alive", "text/plain"); });

    /* Data endpoint */
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

                    std::ofstream file(
                        "D:\\Mahmood_Reda\\SmartIoT-Assistant\\data\\input.json",
                        std::ios::trunc);

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

    // Blocking call (will exit when server.stop() is called)
    server.listen("0.0.0.0", 8080);
}
