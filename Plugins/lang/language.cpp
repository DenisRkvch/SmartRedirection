#include "language.h"
#include "core/ICondition.h"
#include "core/ICommand.h"
#include "core/IoCContainer/IoCCore/IoC.h"
#include "core/IoCContainer/IoCConnectContainerCommand.h"
#include "third_party/json.hpp"


using json = nlohmann::json;


class LangCondition : public ICondition {
public:
    LangCondition(const std::string& arg, const json& context)
        : target_language_(arg), context_(context)
    {
        // Приводим язык к нижнему регистру
        std::transform(target_language_.begin(), target_language_.end(),
            target_language_.begin(), ::tolower);
    }

    bool check() override {
        // 1. Извлекаем Accept-Language из контекста
        std::string accept_language;
        try {
            accept_language = context_["headers"].at("Accept-Language").get<std::string>();
        }
        catch (...) {
            return false; // Если заголовок отсутствует
        }

        // 2. Приводим к нижнему регистру для сравнения
        std::transform(accept_language.begin(), accept_language.end(),
            accept_language.begin(), ::tolower);

        // 3. Разбиваем на отдельные языки
        size_t pos = 0;
        while ((pos = accept_language.find(',')) != std::string::npos) {
            std::string lang = accept_language.substr(0, pos);
            accept_language.erase(0, pos + 1);

            // Удаляем вес качества (q=0.9)
            size_t q_pos = lang.find(';');
            if (q_pos != std::string::npos) {
                lang = lang.substr(0, q_pos);
            }

            // Проверяем совпадение
            if (lang == target_language_) {
                return true;
            }
        }

        // Проверяем последний язык
        return accept_language == target_language_;
    }

private:
    std::string target_language_;
    json context_;
};

void LanugPlugin::execute()
{
    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.language.language="),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new LangCondition(str,j);
    })
    )->execute();
}

extern "C" {

    PLUGIN_API IPlugin* create_plugin_object(void) {
        return new LanugPlugin();
    }

    PLUGIN_API void destroy_plugin_object(IPlugin* obj) {
        delete obj;
    }

    CONNECT_IOC void plugin_connect_ioc(IIoCContainer* container) {
        IoCConnectContainerCommand iocconnectcmd(container);
        iocconnectcmd.execute();
    }
}