#include "PluginException.h"

PluginException::PluginException (const std::string& str) noexcept : runtime_error("PluginException: " + str)
{
}

