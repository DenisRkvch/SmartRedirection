#include "RegisterConditionsCommand.h"
#include "../IoCContainer/IoCCore/IoC.h"
#include "../ICondition.h"
#include "../../third_party/json.hpp"
#include "../IPlugin.h"
#include "../Conditions/PathNameEqCondition.h"
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"

using json = nlohmann::json;

void RegisterConditionsCommand::execute(void)
{
    // main scope init
    IoC::Resolve<ICommand*>("IoC.Scope.New", std::string("Main"))->execute();
    IoC::Resolve<ICommand*>("IoC.Scope.Current", std::string("Main"))->execute();

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions"),
        New_Resolver((std::function<ICondition * (std::string, std::string, json)>)[](const std::string& cond_name, const std::string& arg, const json& context)->ICondition*
    {
        ICondition* condition;
        try {
            // поиск правила в ioc
            condition = IoC::Resolve<ICondition*>(std::string("Conditions." + cond_name), arg, context);
        }
        catch (std::exception&)
        {
            // если в ioc не найдено, то ищем плагин с таким именем и выполняем его
            IoC::Resolve<IPlugin*>("Plugins", cond_name)->execute();

            IoC::Resolve<ILogger*>("Logger")->log("plugin included! => ");

            // повторный поиск в ioc после регистрации 
            condition = IoC::Resolve<ICondition*>("Conditions." + cond_name, arg, context);

        }
        return condition;
    })
    )->execute();

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.path.name="),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](const std::string& path, const json& context)->ICondition* {
        return new PathNameEqCondition(path, context);
    })
    )->execute();

    IoC::Resolve<ICommand*>("IoC.Scope.Current", std::string("Root"))->execute();

}
