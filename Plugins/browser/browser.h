#pragma once

#include "core/IPlugin.h"
#include "plugins/plugin_api_dll.h"
#include "plugins/connect_ioc_api_dll.h"


class BrowserPlugin : public IPlugin
{
	// ������������ ����� IPlugin
	void execute() override;
};