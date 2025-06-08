#include "time.h"
#include "core/ICondition.h"
#include "core/ICommand.h"
#include "core/IoCContainer/IoCCore/IoC.h"
#include "core/IoCContainer/IoCConnectContainerCommand.h"
#include "third_party/json.hpp"

#include <windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <regex>

using json = nlohmann::json;


class TimeConditionBase : public ICondition {
protected:
    SYSTEMTIME get_local_time() const {
        SYSTEMTIME st;
        GetLocalTime(&st);
        return st;
    }

    // Утилита для конвертации строки в число
    int parse_int(const std::string& s) const {
        try {
            return std::stoi(s);
        }
        catch (...) {
            throw std::runtime_error("Invalid number format: " + s);
        }
    }

    // Парсинг формата "[start, end]"
    std::pair<int, int> parse_range(const std::string& range_str) const {
        // Регулярное выражение для разбора формата
        std::regex range_regex(R"(\s*\[\s*(\d+)\s*,\s*(\d+)\s*\]\s*)");
        std::smatch match;

        if (std::regex_match(range_str, match, range_regex)) {
            return {
                parse_int(match[1].str()),
                parse_int(match[2].str())
            };
        }

        throw std::runtime_error("Invalid range format: " + range_str);
    }
};



class TimeHourEqCondition : public TimeConditionBase {
public:
    TimeHourEqCondition(const std::string& str) : hour(parse_int(str)) {}
    bool check() override {
        SYSTEMTIME st = get_local_time();
        return st.wHour == hour;
    }
private: 
    int hour;
};

class TimeDayEqCondition : public TimeConditionBase {
public:
    TimeDayEqCondition(const std::string& str) : day(parse_int(str)) {}
    bool check() override {

        SYSTEMTIME st = get_local_time();
        return st.wDay == day;
    }
private:
    int day;
};

class TimeMonthEqCondition : public TimeConditionBase {
public:
    TimeMonthEqCondition(const std::string& str) : month(parse_int(str)) {}
    bool check() override {

        SYSTEMTIME st = get_local_time();
        return st.wMonth == month;
    }
private:
    int month;
};


// ДИАПАЗОНЫ ОЖИДАЮТСЯ В ФОРМАТЕ "[start, end]"
class TimeHourRangeCondition : public TimeConditionBase {
public:
    TimeHourRangeCondition(const std::string& str) {
        auto val = parse_range(str);
        start = val.first;
        end = val.second;
    }
    bool check() override {
        SYSTEMTIME st = get_local_time();
        return st.wHour >= start && st.wHour <= end;
    }
private:
    int start, end;
};

class TimeDayRangeCondition : public TimeConditionBase {
public:
    TimeDayRangeCondition(const std::string& str) {
        auto val = parse_range(str);
        start = val.first;
        end = val.second;
    }
    bool check() override {
        SYSTEMTIME st = get_local_time();
        return st.wDay >= start && st.wDay <= end;
    }
private:
    int start, end;
};

class TimeMonthRangeCondition : public TimeConditionBase {
public:
    TimeMonthRangeCondition(const std::string& str) {
        auto val = parse_range(str);
        start = val.first;
        end = val.second;
    }
    bool check() override {
        SYSTEMTIME st = get_local_time();
        return st.wMonth >= start && st.wMonth <= end;
    }
private:
    int start, end;
};

void TimePlugin::execute()
{
    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.time.hour="),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
            return new TimeHourEqCondition(str);
    })
    )->execute();

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.time.day="),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new TimeDayEqCondition(str);
    })
    )->execute();

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.time.month="),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new TimeMonthEqCondition(str);
    })
    )->execute();


    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.time.hour:range"),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new TimeHourRangeCondition(str);
    })
    )->execute();

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.time.day:range"),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new TimeDayRangeCondition(str);
    })
    )->execute();

    IoC::Resolve<ICommand*>(
        std::string("IoC.Register"),
        std::string("Conditions.time.month:range"),
        New_Resolver((std::function<ICondition * (std::string, json)>)[](std::string str, json j)->ICondition* {
        return new TimeMonthRangeCondition(str);
    })
    )->execute();

}

extern "C" {

    PLUGIN_API IPlugin* create_plugin_object(void) {
        return new TimePlugin();
    }

    PLUGIN_API void destroy_plugin_object(IPlugin* obj) {
        delete obj;
    }

    CONNECT_IOC void plugin_connect_ioc(IIoCContainer* container) {
        IoCConnectContainerCommand iocconnectcmd(container);
        iocconnectcmd.execute();
    }
}