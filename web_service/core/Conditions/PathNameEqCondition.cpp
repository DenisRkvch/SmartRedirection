#include "PathNameEqCondition.h"
#include "../Exceptions/ConditionException.h"

PathNameEqCondition::PathNameEqCondition(const std::string& str, const json& json) : path(str), context(json)
{
}

bool PathNameEqCondition::check()
{
    // Извлекаем путь (до символа '?')
    if (!context.contains("target")) { throw ConditionException("UrlPathCondition: context doesn't contain 'target'"); }
    size_t pos = context["target"].get<std::string>().find('?');
    std::string context_path = context["target"].get<std::string>().substr(0, pos);
    return context_path == path;
}