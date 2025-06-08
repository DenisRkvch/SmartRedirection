#include "NestedTarget.h"
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"



NestedTarget::NestedTarget(IRuleExpression* rules) : nestedRules(rules)
{
}

NestedTarget::~NestedTarget()
{
	delete nestedRules;
}

const std::string& NestedTarget::interpret(const nlohmann::json& context)
{
	IoC::Resolve<ILogger*>("Logger")->log("      All check pass for nested rules. Entering them... \n");
	return nestedRules->interpret(context);
}
