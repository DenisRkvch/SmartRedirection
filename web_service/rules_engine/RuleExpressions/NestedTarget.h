#ifndef NESTEDTARGET_H_INCLUDED
#define NESTEDTARGET_H_INCLUDED

#include "IRuleExpression.h"
#include "../../third_party/json.hpp"

#include <string>

class NestedTarget : public IRuleExpression
{
public:
    NestedTarget(IRuleExpression* rules);
    ~NestedTarget();
    const std::string& interpret(const nlohmann::json& context) override;

private:
    IRuleExpression* nestedRules;
};

#endif