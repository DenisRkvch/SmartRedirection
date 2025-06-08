#pragma once
#ifndef USINGTHREADSCOPEDECORATOR_H
#define USINGTHREADSCOPEDECORATOR_H

#include "../rules_engine/IRuleEngine.h"

using json = nlohmann::json;

class UsingThreadScopeDecorator : public IRuleEngine
{
public:
	UsingThreadScopeDecorator(std::shared_ptr<IRuleEngine>);
	const std::string evaluate(const json&) override;

private:
	std::shared_ptr<IRuleEngine> inner;
};

#endif