#include "CheckFailException.h"

CheckFailException::CheckFailException(const std::string& msg) noexcept : runtime_error(msg)
{
}
