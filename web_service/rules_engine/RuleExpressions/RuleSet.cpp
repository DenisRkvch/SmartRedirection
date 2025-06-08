#include "RuleSet.h"
#include "RuleInterpreterException.h"
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"


void RuleSet::addRule(IRuleExpression* rule)
{
	rules.push_back(rule);
}

RuleSet::~RuleSet()
{
    for (auto rule : rules) {
        delete rule;
    }
}

const std::string& RuleSet::interpret(const nlohmann::json& context)
{
    for (auto& rule : rules) {
        try {
            return rule->interpret(context);
        }
        catch (std::exception& e) {
            IoC::Resolve<ILogger*>("Logger")->log("  Rule not passed: " + std::string(e.what()) + '\n');
        }
        // ѕродолжаем провер€ть следующие правила
        IoC::Resolve<ILogger*>("Logger")->log("\n");

    }
    //throw RuleInterpreterException("No matching rule");
    throw std::runtime_error("No matching rule");
}