#ifndef IOC_H
#define IOC_H

#include <string>
#include <functional>
#include "IFunctor.h"
#include "IIoCContainer.h"

class IoC
{
public:

    template<typename T, typename... Args>
    static T Resolve(const std::string& key, Args... args)
    {
        return (**ioCContainer_ptr)[key]->call<T, Args...>(args...);
        
    }

private:

    static IIoCContainer** ioCContainer_ptr;
    class DefaultIoCContainer;
    

};

template<class T, typename... Args>
inline IFunctor* New_Resolver(std::function<T(Args...)> f)
{
    return new Functor<T, Args...>(f);
}

template<class T, typename... Args>
inline IFunctor* New_Resolver(T(*f)(Args...))
{
    return new Functor<T, Args...>((std::function<T(Args...)>)f);
}

#endif


