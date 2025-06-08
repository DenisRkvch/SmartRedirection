#ifndef REDIRECTOR_REQUEST_HANDLER_H_INCLUDED
#define REDIRECTOR_REQUEST_HANDLER_H_INCLUDED

#include "IRequestHandler.h"
#include <boost/asio/ip/tcp.hpp>
#include "../rules_engine/IRuleEngine.h"

class RedirectorRequestHandler : public IRequestHandler
{
public:
	RedirectorRequestHandler(std::shared_ptr<IRuleEngine>);

	void handleRequest(boost::asio::ip::tcp::socket socket) override;

private:
	std::shared_ptr<IRuleEngine> rule_engine;
};

#endif
