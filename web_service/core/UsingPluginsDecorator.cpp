#include "UsingPluginsDecorator.h"
#include "../plugins/IoCPluginManager.h"
#include "IoCContainer/ScopeTree.h"
#include "ICommand.h"
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"

UsingPluginsDecorator::UsingPluginsDecorator(std::shared_ptr<IRuleEngine> engine) : inner(engine){}


const std::string UsingPluginsDecorator::evaluate(const json& context) {
    // инициализаци€ менеджера плагинов. закрывает плагины при выходе

    IoC::Resolve<ILogger*>("Logger")->log("SETTING UP PLUGIN ENVIROMENT \n");
    IoCPluginManager plug_manager(&ScopeTree::getScopeTreeInstance());

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Plugins"),
        New_Resolver((std::function<IPlugin * (std::string)>)[&plug_manager](const std::string& plugin_name)->IPlugin*
    {
        // вычлени€ем часть до точки
        std::string base = plugin_name;
        size_t pos = base.find('.');
        if (pos != std::string::npos) {
            base = plugin_name.substr(0, pos);
        }

        IoC::Resolve<ILogger*>("Logger")->log("Try find and include plugin '" + base + "'... => ");

        return plug_manager.loadPlugin("plugins/" + base + ".dll");
    })
    )->execute();

    return inner->evaluate(context);
}