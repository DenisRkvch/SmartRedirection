#include "HttpServer.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"

namespace net = boost::asio;
using tcp = net::ip::tcp;

HttpServer::HttpServer(std::string address, unsigned short port, IRequestHandler* handler) :  
    io_context(), acceptor(io_context, tcp::endpoint(net::ip::make_address(address), port)), request_handler(handler)
{}

HttpServer::~HttpServer() {
    stop();
    if (server_thread.joinable()) { server_thread.join(); }
}

void HttpServer::start()
{
    if (running) return;
    running = true;


    IoC::Resolve<ILogger*>("Logger")->log("Server listening on http://" + acceptor.local_endpoint().address().to_string() + 
         ":" + std::to_string(acceptor.local_endpoint().port()) + "\n");

    startAsyncAccept();

    // Запуск цикла обработки событий в отдельном потоке
    server_thread = std::thread([this]() {      
        io_context.run();
    });
}

void HttpServer::stop()
{
    if (!running) return;
    running = false;

    acceptor.close();   // (прерывает async_accept) 
    io_context.stop();  // (прерывает все асинхронные операции)
}

void HttpServer::startAsyncAccept()
{
    acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec)
        {
            // Запускаем обработчик запроса в отдельном потоке
            std::thread([this, sock = std::move(socket)]() mutable {
                request_handler->handleRequest(std::move(sock));
                }).detach();

        }
        else if (ec != net::error::operation_aborted) {
            IoC::Resolve<ILogger*>("Logger")->log("Server accept error: " + ec.message() + "\n");
        }

        // Запускаем следующий асинхронный accept
        if (running) {
            startAsyncAccept();
        }
    });
}
