#ifndef CHAINMESSAGEHANDLER_H
#define CHAINMESSAGEHANDLER_H

#include "../endpoint/IMessageHandler.h"
#include <memory>

class ChainMessageHandler : public IMessageHandler
{
public:
    virtual ~ChainMessageHandler() = default;

    void setNext(std::shared_ptr<IMessageHandler> next);

    void handleMessage(const std::vector<uint8_t>& raw_data) override;

protected:
    virtual void processMessage(const std::vector<uint8_t>& raw_data) = 0;

private:
    std::shared_ptr<IMessageHandler> nextHandler;
};
#endif

