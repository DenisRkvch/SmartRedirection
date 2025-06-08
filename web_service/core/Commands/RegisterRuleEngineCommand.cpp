#include "RegisterRuleEngineCommand.h"

#include "../IoCContainer/IoCCore/IoC.h"
#include "../../rules_engine/IRuleEngine.h"
#include "../../utils/JsonFileLoader.h"
#include "../../rules_engine/RuleAstBuilder.h"
#include "../../rules_engine/RuleInterpreter.h"
#include "../UsingPluginsDecorator.h"
#include "../UsingThreadScopeDecorator.h"



void RegisterRuleEngineCommand::execute(void)
{

    // �������� ���������� ������
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("JsonFileLoader"),
        New_Resolver((std::function<std::shared_ptr<JsonFileLoader>()>)[]()->std::shared_ptr<JsonFileLoader> {
            return std::make_shared<JsonFileLoader>("rules_config.json");
        })
    )->execute();


    // �������� ������� ������
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("RuleAstBuilder"),
        New_Resolver((std::function< std::shared_ptr<RuleAstBuilder> ()>)[]()->std::shared_ptr<RuleAstBuilder>{
            return std::make_shared<RuleAstBuilder>(IoC::Resolve<std::shared_ptr<JsonFileLoader>>("JsonFileLoader"));
        })
    )->execute();


    // �������� �������������� ������
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("RuleInterpreter"),
        New_Resolver((std::function<std::shared_ptr<RuleInterpreter>()>)[]()->std::shared_ptr<RuleInterpreter> {
            return std::make_shared<RuleInterpreter>(IoC::Resolve<std::shared_ptr<RuleAstBuilder>>("RuleAstBuilder"));
        })
    )->execute();

    // �������� ���������� ��� ��������������� ��� ������ � ��������� 
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("UsingPluginsDecorator"),
        New_Resolver((std::function< std::shared_ptr<UsingPluginsDecorator> ()>)[]() ->std::shared_ptr<UsingPluginsDecorator> {
            return std::make_shared <UsingPluginsDecorator>(IoC::Resolve<std::shared_ptr<RuleInterpreter>>("RuleInterpreter"));
        })
    )->execute();


    // �������� ���������� ��� ��������������� ��� ������������� ������ � ������ ������
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("UsingThreadScopeDecorator"),
        New_Resolver((std::function<std::shared_ptr<UsingThreadScopeDecorator>()>)[]()->std::shared_ptr<UsingThreadScopeDecorator> {

            return std::make_shared<UsingThreadScopeDecorator>(IoC::Resolve<std::shared_ptr<UsingPluginsDecorator>>("UsingPluginsDecorator"));

    })
    )->execute();


    // �������� ���������� ������ ������
    IoC::Resolve<ICommand*>(
        "IoC.Register",
        std::string("RuleEngine"),
        New_Resolver((std::function<std::shared_ptr<IRuleEngine> ()>)[]() ->std::shared_ptr<IRuleEngine> {
            return IoC::Resolve<std::shared_ptr<UsingThreadScopeDecorator>>("UsingThreadScopeDecorator");
        })
    )->execute();

}
