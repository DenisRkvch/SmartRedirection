#ifndef JSONFILELOADER_H
#define JSONFILELOADER_H

#include "IJsonProvider.h"
#include "../third_party/json.hpp"

using json = nlohmann::json;

class JsonFileLoader : public IJsonProvider
{

public:
	JsonFileLoader(const std::string& path);
	json getJson() override;

private:
	std::string path_to_json;
};

#endif