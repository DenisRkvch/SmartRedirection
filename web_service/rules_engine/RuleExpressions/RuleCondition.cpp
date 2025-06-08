#include "RuleCondition.h"
#include "RuleInterpreterException.h"
#include "CheckFailException.h"
#include "../../core/ICondition.h"
#include "../../core/IoCContainer/IoCCore/IoC.h"
#include "../../core/IoCContainer/IoCCore/IoCException.h"

#include "../logger/ILogger.h"

#include <stdexcept>



RuleCondition::RuleCondition(const std::string& name_str, const std::string& value_str, IRuleExpression* next_rule):
	name(name_str), value(value_str), next(next_rule)
{
}

RuleCondition::~RuleCondition()
{
    delete next;
}

const std::string& RuleCondition::interpret(const nlohmann::json& context)
{
    IoC::Resolve<ILogger*>("Logger")->log("      Interpret condition: " + name + " :: " + value + "    => ");
    ICondition* condition;
    try {
        condition = IoC::Resolve<ICondition*>("Conditions", name, value, context);
    }
    catch(IoCException& e){       
        throw RuleInterpreterException("Don't know how interpret condition '" + name + "': " + e.what());
    }

    IoC::Resolve<ILogger*>("Logger")->log("CHECK... => ");
    bool result;
    try {
        result = condition->check();
    }
    catch (std::exception& e){
        delete condition;
        throw RuleInterpreterException("Check error: " + std::string(e.what()));
    }

    delete condition;

	if (result)
	{
        IoC::Resolve<ILogger*>("Logger")->log("PASSED \n");
        return next->interpret(context);
	}

    IoC::Resolve<ILogger*>("Logger")->log("FAILED ");

    throw CheckFailException("Condition check failed");
}
