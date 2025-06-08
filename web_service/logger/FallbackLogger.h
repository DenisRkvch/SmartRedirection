#ifndef FALLBACKLOGGER_H
#define FALLBACKLOGGER_H

#include "ILogger.h"

class FallbackLogger : public ILogger {
public:
    void log(const std::string& message) override;
};

#endif