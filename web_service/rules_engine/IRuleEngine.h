#ifndef IRULEENGINE_H_INCLUDED
#define IRULEENGINE_H_INCLUDED

#include <string>
#include "../third_party/json.hpp"


class IRuleEngine
{
public:
    virtual ~IRuleEngine() = default;
    virtual const std::string evaluate(const nlohmann::json&) = 0;


};

#endif // IRULEENGINE_H_INCLUDED