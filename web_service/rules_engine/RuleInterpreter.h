#ifndef RULINTERPRETER
#define RULINTERPRETER

#include "IRuleEngine.h"
#include "IRuleProvider.h"

using json = nlohmann::json;

class RuleInterpreter : public IRuleEngine
{
public:
	RuleInterpreter(std::shared_ptr<IRuleProvider>);
	const std::string evaluate(const json&) override;

private:
	std::shared_ptr<IRuleProvider> builder;
};

#endif