#include "browser.h"
#include "core/ICondition.h"
#include "core/ICommand.h"
#include "core/IoCContainer/IoCCore/IoC.h"
#include "core/IoCContainer/IoCConnectContainerCommand.h"
#include "third_party/json.hpp"


using json = nlohmann::json;

class BrowserNameCondition : public ICondition {
public:
    BrowserNameCondition(const std::string& arg, const json& context)
        : target_browser_(arg), context_(context)
    {
        // �������� �������� �������� � ������� ��������
        std::transform(target_browser_.begin(), target_browser_.end(),
            target_browser_.begin(), ::tolower);
    }

    bool check() override {
        // 1. ��������� User-Agent �� ���������
        std::string Sec_CH_UA;
        try {
            Sec_CH_UA = context_["headers"].at("sec-ch-ua").get<std::string>();
        }
        catch (...) {
            return false; // ���� ��������� �����������
        }

        // 2. �������� � ������� �������� ��� ���������
        std::transform(Sec_CH_UA.begin(), Sec_CH_UA.end(),
            Sec_CH_UA.begin(), ::tolower);
     
        return Sec_CH_UA.find(target_browser_) != std::string::npos;
    }

private:
    std::string target_browser_;
    json context_;
};


class BrowserVersionGtrCondition : public ICondition {
public:
    BrowserVersionGtrCondition(const std::string& arg, const json& context)
        : target_version_(arg), context_(context) {
    }

    bool check() override {
        // 1. ��������� Sec-CH-UA �� ���������
        std::string sec_ch_ua;
        try {
            sec_ch_ua = context_["headers"].at("sec-ch-ua").get<std::string>();
        }
        catch (...) {
            return false; // ���� ��������� �����������
        }

        // 2. ��������� ������ �������� �� ���������
        std::string version = extract_version(sec_ch_ua);
        if (version.empty()) return false;

        // 3. ���������� � ������� �������
        return version == target_version_;
    }

private:
    // ������� ������� ������ �� Sec-CH-UA
    std::string extract_version(const std::string& sec_ch_ua) {
        // ���� ������ ������ (;v=")
        size_t start = sec_ch_ua.find(";v=\"");
        if (start == std::string::npos) return "";

        // ���������� ;v="
        start += 4;

        // ���� ����� ������
        size_t end = sec_ch_ua.find('"', start);
        if (end == std::string::npos) return "";

        // ��������� ��������� � �������
        return sec_ch_ua.substr(start, end - start);
    }

    std::string target_version_;
    json context_;
};

void BrowserPlugin::execute()
{
    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.browser.name="),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new BrowserNameCondition(str, j);
    })
    )->execute();

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.browser.version="),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new BrowserNameCondition(str, j);
    })
    )->execute();
}

extern "C" {

    PLUGIN_API IPlugin* create_plugin_object(void) {
        return new BrowserPlugin();
    }

    PLUGIN_API void destroy_plugin_object(IPlugin* obj) {
        delete obj;
    }

    CONNECT_IOC void plugin_connect_ioc(IIoCContainer* container) {
        IoCConnectContainerCommand iocconnectcmd(container);
        iocconnectcmd.execute();
    }
}
