#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"
#include "RuleInterpreterException.h"
#include "SingleRule.h"

SingleRule::SingleRule(IRuleExpression* last_expression_ptr, std::string target) : chain(last_expression_ptr), target_name(target)
{
}

SingleRule::~SingleRule()
{
    delete chain;
}

const std::string& SingleRule::interpret(const nlohmann::json& context)
{
    IoC::Resolve<ILogger*>("Logger")->log("  Checking rules for target: " + target_name + "\n");

    const std::string& result = chain->interpret(context);

    IoC::Resolve<ILogger*>("Logger")->log("  All check pass for target: " + target_name + "\n");

    return result;
}
