#ifndef IPLUGINMANAGER_H_INCLUDED
#define IPLUGINMANAGER_H_INCLUDED

#include "../core/IPlugin.h"
#include <string>

class IPluginManager 
{
public:
	virtual ~IPluginManager() = default;

	virtual IPlugin* loadPlugin(const std::string&) = 0;
};


#endif
