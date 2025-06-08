#include "RuleInterpreter.h"
#include "RuleExpressions/IRuleExpression.h"

RuleInterpreter::RuleInterpreter(std::shared_ptr<IRuleProvider> provider) : builder(provider)
{}


const std::string RuleInterpreter::evaluate(const json& context)
{
	IRuleExpression* rules;

	try {
		rules = builder->getRule();
	}
	catch(std::exception& e) {
		throw std::runtime_error("RuleInterpreter: no rules given: " + std::string(e.what()));
	}

	std::string str;

	try{
		str = rules->interpret(context);

	}
	catch(std::exception& e){
		delete rules;
		throw std::runtime_error("RuleInterpreter: Don't know how to interpret rules: " + std::string(e.what()));
	}

	delete rules;
	return std::move(str);
}