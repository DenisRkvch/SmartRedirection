#pragma once
#include <stdexcept>

class RuleInterpreterException : public std::runtime_error
{
public:
	RuleInterpreterException(const std::string& msg = "no description") noexcept;
};