#ifndef IRULEPROVIDER_H_INCLUDED
#define IRULEPROVIDER_H_INCLUDED

#include "RuleExpressions/IRuleExpression.h"

class IRuleProvider
{
public:
    virtual ~IRuleProvider() = default;
    virtual IRuleExpression* getRule() = 0;
};

#endif // IRULEPROVIDER_H_INCLUDED