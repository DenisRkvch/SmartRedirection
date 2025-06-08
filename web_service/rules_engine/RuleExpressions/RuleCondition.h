#ifndef RULECONDITION_H_INCLUDED
#define RULECONDITION_H_INCLUDED

#include "IRuleExpression.h"
#include "../../third_party/json.hpp"
#include <string>

class RuleCondition : public IRuleExpression {
public:
    ~RuleCondition();

    RuleCondition(const std::string&, const std::string&, IRuleExpression*);
    const std::string& interpret(const nlohmann::json& context) override;

private:
    std::string name;
    std::string value;
    IRuleExpression* next;
    
};


#endif