#ifndef IJSONPROVIDER_H
#define IJSONPROVIDER_H

#include "../third_party/json.hpp"

class IJsonProvider 
{
public:
	virtual ~IJsonProvider() = default;
	virtual nlohmann::json getJson() = 0;

};
#endif
