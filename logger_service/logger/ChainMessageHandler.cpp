#include "ChainMessageHandler.h"


void ChainMessageHandler::setNext(std::shared_ptr<IMessageHandler> next)
{
	nextHandler = next;
}

void ChainMessageHandler::handleMessage(const std::vector<uint8_t>& raw_data)
{
    processMessage(raw_data);
    if (nextHandler) {
        nextHandler->handleMessage(raw_data);
    }
}
