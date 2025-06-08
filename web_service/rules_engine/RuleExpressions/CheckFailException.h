#pragma once
#include <stdexcept>

class CheckFailException : public std::runtime_error
{
public:
	CheckFailException(const std::string& msg = "no description") noexcept;
};