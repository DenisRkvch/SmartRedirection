#pragma once

#include "../core/IPlugin.h"

#ifdef PLUGIN_EXPORTS
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#endif


extern "C" {
	PLUGIN_API IPlugin* create_plugin_object(void);
	PLUGIN_API void destroy_plugin_object(IPlugin*);
}
