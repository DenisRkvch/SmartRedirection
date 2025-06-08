#ifndef I_REQUEST_HANDLER_H_INCLUDED
#define I_REQUEST_HANDLER_H_INCLUDED

#include <boost/asio/ip/tcp.hpp>

class IRequestHandler
{

public:
    virtual ~IRequestHandler() = default;
    virtual void handleRequest(boost::asio::ip::tcp::socket) = 0;
};

#endif // I_REQUEST_HANDLER_H_INCLUDED