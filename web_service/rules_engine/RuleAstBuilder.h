#ifndef RULEASTBUILDER_H_INCLUDED
#define RULEASTBUILDER_H_INCLUDED

#include "IRuleProvider.h"
#include "../utils/IJsonProvider.h"
#include "RuleExpressions/IRuleExpression.h"
#include "../third_party/json.hpp"


class RuleAstBuilder : public IRuleProvider{
    

public:
    RuleAstBuilder(std::shared_ptr <IJsonProvider> h);

    IRuleExpression* getRule() override;

private:
    IRuleExpression* build(const nlohmann::json& rule);
    IRuleExpression* parseRule(const nlohmann::json& rule);

    std::shared_ptr <IJsonProvider> json_provider;
};

#endif