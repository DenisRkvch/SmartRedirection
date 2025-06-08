#ifndef RULEEXPRESSION_H_INCLUDED
#define RULEEXPRESSION_H_INCLUDED

#include <string>
#include "../../third_party/json.hpp"


class IRuleExpression {
public:
    virtual ~IRuleExpression() = default;
    virtual const std::string& interpret(const nlohmann::json& context) = 0;
};

#endif