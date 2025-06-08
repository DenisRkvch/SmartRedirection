#ifndef SCOPETREE_H
#define SCOPETREE_H

#include <map>
#include "IoCCore/IFunctor.h"
#include "IoCCore/IIoCContainer.h"
#include "Scope.h"
#include "IoCCore/IoC.h"


class ScopeTree : public IIoCContainer
{

public:

    IFunctor *operator [](const std::string& str) override;
    static ScopeTree& getScopeTreeInstance();
    static const std::string& getCurScopeId();

private:

    static Scope root_scope;
    static thread_local IScope* curScopePtr;

};



#endif // SCOPETREE_H

