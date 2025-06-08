#include "InitIoCContainerCommand.h"
#include "../IoCContainer/IoCCore/IoC.h"
#include "../IoCContainer/IoCConnectContainerCommand.h"
#include "../IoCContainer/ScopeTree.h"

void InitIoCContainerCommand::execute(void)
{
    // ioc init
    IoCConnectContainerCommand iocconnectcmd(&ScopeTree::getScopeTreeInstance());
    iocconnectcmd.execute();
}
