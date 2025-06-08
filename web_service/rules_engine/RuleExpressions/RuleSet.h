#ifndef RULESET_H_INCLUDED
#define RULESET_H_INCLUDED

#include "IRuleExpression.h"
#include "../../third_party/json.hpp"

class RuleSet : public IRuleExpression
{
public:
    const std::string& interpret(const nlohmann::json& context) override;
    ~RuleSet();
    void addRule(IRuleExpression*);

private:

    std::vector<IRuleExpression*> rules;
};

#endif