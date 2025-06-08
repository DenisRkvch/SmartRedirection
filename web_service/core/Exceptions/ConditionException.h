#ifndef CONDITIONEXCEPTION_H_INCLUDED
#define CONDITIONEXCEPTION_H_INCLUDED

#include <stdexcept>
#include <string>

class ConditionException : public std::runtime_error
{
public:
    ConditionException(const std::string& message = "no description") noexcept;
};

#endif 
