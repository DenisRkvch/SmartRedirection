#include "CommandException.h"

CommandException::CommandException(const std::string& what_arg) noexcept : runtime_error("Command Exception: " + what_arg)
{
}
