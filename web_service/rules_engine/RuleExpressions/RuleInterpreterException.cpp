#include "RuleInterpreterException.h"

RuleInterpreterException::RuleInterpreterException(const std::string& msg) noexcept : runtime_error("Rule Interpreter Exception: " + msg) 
{}

