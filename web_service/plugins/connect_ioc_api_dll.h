#pragma once

#include "../core/IoCContainer/IoCCore/IIoCContainer.h"

#ifdef CONNECT_IOC_EXPORTS
#define CONNECT_IOC __declspec(dllexport)
#else
#define CONNECT_IOC __declspec(dllimport)
#endif

extern "C" {
	CONNECT_IOC void plugin_connect_ioc(IIoCContainer*);
}