#ifndef CONSOLELOGGERHANDLER_H
#define CONSOLELOGGERHANDLER_H

#include "ChainMessageHandler.h"

class ConsoleLoggerHandler : public ChainMessageHandler
{
private:
	// Унаследовано через ChainMessageHandler
	void processMessage(const std::vector<uint8_t>& raw_data) override;

};
#endif // CONSOLELOGGERHANDLER_H
