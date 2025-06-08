#ifndef USINGPLUGINSDECORATOR_H
#define USINGPLUGINSDECORATOR_H

#include "../rules_engine/IRuleEngine.h"

using json = nlohmann::json;

class UsingPluginsDecorator : public IRuleEngine
{
public:
	UsingPluginsDecorator(std::shared_ptr<IRuleEngine>);
	const std::string evaluate(const json&) override;

private:
	std::shared_ptr<IRuleEngine> inner;
};

#endif