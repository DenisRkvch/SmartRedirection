#ifndef SINGLERULE_H_INCLUDED
#define SINGLERULE_H_INCLUDED

#include "IRuleExpression.h"
#include "../../third_party/json.hpp"
#include <string>

class SingleRule : public IRuleExpression 
{
public:
    SingleRule(IRuleExpression* last_expression_ptr, std::string target);
    ~SingleRule();
    const std::string& interpret(const nlohmann::json& context) override;

private:
    IRuleExpression* chain;
    std::string target_name;
};

#endif