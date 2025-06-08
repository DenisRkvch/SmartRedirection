#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>
#include <thread>
#include <atomic>
#include "IRequestHandler.h"

class HttpServer
{
public:
    HttpServer(std::string address, unsigned short port, IRequestHandler*);
    ~HttpServer();

    void start();
    void stop();

private:
    void startAsyncAccept();

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    IRequestHandler* request_handler;

    std::atomic<bool> running = false;
    std::thread server_thread;
};

#endif // ICOMMAND_H