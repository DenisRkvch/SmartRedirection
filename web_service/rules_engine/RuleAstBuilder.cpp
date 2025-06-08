#include "RuleAstBuilder.h"
#include "RuleExpressions/RuleSet.h"
#include "RuleExpressions/SingleRule.h"
#include "RuleExpressions/RuleCondition.h"
#include "RuleExpressions/StringTarget.h"
#include "RuleExpressions/NestedTarget.h"

#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"

using json = nlohmann::json;

RuleAstBuilder::RuleAstBuilder(std::shared_ptr <IJsonProvider> provider) : json_provider(provider)
{
}

// ѕроверка наличи€ ключа и типа в json
static void validateKey(const json& j, const std::string& key, json::value_t expectedType) {
    if (!j.contains(key)) {
        throw std::runtime_error("RuleBuilder: invalid json format: missing required key: '" + key + "'");
    }
    if (j[key].type() != expectedType) {
        throw std::runtime_error("RuleBuilder: invalid json format: key '" + key + "' has invalid type");
    }
}

IRuleExpression* RuleAstBuilder::getRule()
{
    json rules;
    try {
        rules = json_provider->getJson();
    }
    catch (std::exception& e) {
        throw std::runtime_error(std::string("RuleBuilder: no Json given: ") + e.what());
    }

    validateKey(rules, "Rules", nlohmann::json::value_t::array);

    return build(rules);
}



IRuleExpression* RuleAstBuilder::build(const json& rules)
{
    RuleSet* rule_set = new RuleSet;

    for (const auto& rule : rules["Rules"]) {
        try {
            // ѕроверка структуры каждого правила
            if (!rule.is_object()) {
                throw std::runtime_error("RuleBuilder: invalid json format: rule must be a json object");
            }
            validateKey(rule, "conditions", json::value_t::object);
            if (!rule.contains("target")) {
                throw std::runtime_error("RuleBuilder: invalid json format: missing required key: 'target'");
            }
            if ((rule["target"].type() != json::value_t::string) &&
                (rule["target"].type() != json::value_t::object)) {
                throw std::runtime_error("RuleBuilder: invalid json format: key 'target' has invalid type");
            }
            
            rule_set->addRule(parseRule(rule));
        }
        catch (const std::exception& e) {
            IoC::Resolve<ILogger*>("Logger")->log("Rule build skipped: " + std::string(e.what()) + "\n");
        }
    }
    return rule_set;
}

IRuleExpression* RuleAstBuilder::parseRule(const json& rule)
{
    IRuleExpression* chain_ptr;
    std::string target_name;

    // парсинг цели - как последнее звено в цепочке обработчиков
    if (rule["target"].is_string()) {
        // либо цель конечна€ - строка
        target_name = rule["target"].get<std::string>();
        chain_ptr = new StringTarget(target_name);
    }
    else if (rule["target"].is_object()) {
        // либо цель вложенна€ - другой набор правил
        validateKey(rule["target"], "Rules",json::value_t::array);
        target_name = "<nested rules>";
        chain_ptr = new NestedTarget(build(rule["target"]));
    }
    else {
        throw std::runtime_error("RuleBuilder: invalid json format: invalid 'target' type");
    }

    // ѕарсим услови€
    for (auto& [field, value] : rule["conditions"].items()) {
        if (!value.is_string()) {
            throw std::runtime_error("RuleBuilder: invalid json format: condition value must be string for field: " + field);
        }
        chain_ptr = new RuleCondition(field, value.get<std::string>(), chain_ptr);
    }

    return new SingleRule(chain_ptr, target_name);
}

