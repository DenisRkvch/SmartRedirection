#include "StringTarget.h"
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"

StringTarget::StringTarget(const std::string& str) : str_target(str)
{
}

const std::string& StringTarget::interpret(const nlohmann::json& context)
{
	IoC::Resolve<ILogger*>("Logger")->log("    Matched URL: " + str_target + "\n");
	return str_target;
}
