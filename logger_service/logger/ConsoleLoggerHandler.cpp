#include <iostream>
#include "ConsoleLoggerHandler.h"

void ConsoleLoggerHandler::processMessage(const std::vector<uint8_t>& raw_data)
{
	std::cout << std::string(raw_data.begin(), raw_data.end());
}
