#ifndef PATHNAMEEQCONDITION_H
#define PATHNAMEEQCONDITION_H

#include "../ICondition.h"
#include <string>
#include "../../third_party/json.hpp"

using json = nlohmann::json;

class PathNameEqCondition : public ICondition {
public:
    PathNameEqCondition(const std::string& str, const json& json);

    // Унаследовано через ICondition
    bool check() override;

private:
    std::string path;
    json context;
};
#endif