#include "UsingThreadScopeDecorator.h"
#include "IoCContainer/IoCCore/IoC.h"
#include <thread>
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"
#include "ICommand.h"

class IoCScopeGuard
{
public:
    IoCScopeGuard()
    {
        std::ostringstream oss;
        oss << std::this_thread::get_id();
        std::string thr_id = oss.str();

        IoC::Resolve<ILogger*>("Logger")->log("SETTING UP IoC SCOPE FOR THREAD ID: " + thr_id +"\n");

        IoC::Resolve<ICommand*>("IoC.Scope.Current", std::string("Main"))->execute();
        IoC::Resolve<ICommand*>("IoC.Scope.New", std::string("ThreadId" + thr_id))->execute();
        IoC::Resolve<ICommand*>("IoC.Scope.Current", std::string("ThreadId" + thr_id))->execute();
    }
    ~IoCScopeGuard()
    {
        IoC::Resolve<ILogger*>("Logger")->log("CLEANING UP IOC SCOPE...\n");

        IoC::Resolve<ICommand*>("IoC.Scope.Delete")->execute();
    }
};

UsingThreadScopeDecorator::UsingThreadScopeDecorator(std::shared_ptr<IRuleEngine> engine) : inner(engine)
{
}


const std::string UsingThreadScopeDecorator::evaluate(const json& context)
{
    // создание нового scope для обрабатывающего потока. удаляется при выходе
    IoCScopeGuard  init_scope_for_thread;

    return inner->evaluate(context);
}
