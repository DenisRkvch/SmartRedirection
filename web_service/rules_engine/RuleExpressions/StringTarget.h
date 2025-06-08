#ifndef STRINGTARGET_H_INCLUDED
#define STRINGTARGET_H_INCLUDED

#include "IRuleExpression.h"
#include "../../third_party/json.hpp"

#include <string>

class StringTarget : public IRuleExpression
{
public:
    StringTarget(const std::string& str);
    const std::string& interpret(const nlohmann::json& context) override;

private:
    std::string str_target;
};

#endif