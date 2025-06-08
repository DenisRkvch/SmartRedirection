#ifndef ILOGGER_H_INCLUDED
#define ILOGGER_H_INCLUDED

#include <string>

class ILogger
{
public:
	virtual void log(const std::string& str) = 0;
};
#endif