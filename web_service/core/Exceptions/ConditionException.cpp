#include "ConditionException.h"

ConditionException::ConditionException(const std::string& str) noexcept : runtime_error("ConditionException: " + str)
{
}

