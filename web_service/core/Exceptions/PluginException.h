#ifndef CONDITIONEXCEPTION_H_INCLUDED
#define CONDITIONEXCEPTION_H_INCLUDED

#include <stdexcept>
#include <string>

class PluginException : public std::runtime_error
{
public:
    PluginException (const std::string& message = "no description") noexcept;
};

#endif 
