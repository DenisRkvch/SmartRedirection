#include "FallbackLogger.h"
#include <iostream>

void FallbackLogger::log(const std::string& message)
{
    std::cerr << "[FALLBACK] " << message;
}