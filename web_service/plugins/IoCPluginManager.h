#ifndef DLLPLUGINMANAGER_H_INCLUDED
#define DLLPLUGINMANAGER_H_INCLUDED

#include <string>
#include <unordered_map>
#include <windows.h>
#include "IPluginManager.h"
#include "../core/IoCContainer/IoCCore/IIoCContainer.h"
#include <stdexcept>
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"

class PluginConnectionException : public std::runtime_error {
public:
    PluginConnectionException(const std::string& message = "no description") noexcept : std::runtime_error("PluginConnectionException: " + message)
    {
    };
};

class IoCPluginManager : IPluginManager
{
public:
	IoCPluginManager(IIoCContainer*);
	~IoCPluginManager();

	IPlugin* loadPlugin(const std::string&) override;
	

private:
	std::unordered_map<IPlugin* , HMODULE> open_plugins;
	IIoCContainer* ioc_container;

    void deletePlugin(IPlugin*);

    // обертка для корректного удаления
    class DestructiblePluginWrapper;
    class DestructiblePluginWrapper : public IPlugin
    {
    public:
        DestructiblePluginWrapper(IoCPluginManager* m, IPlugin* p) : plugin(p) {}
        ~DestructiblePluginWrapper()
        {
            try {
                deleter->deletePlugin(plugin);
            }
            catch (PluginConnectionException& e)
            {
                IoC::Resolve<ILogger*>("Logger")->log("Couldn't delete the plugin correctly: " + std::string(e.what()) + "\n");
                delete plugin;
            }
        }
        // Унаследовано через IPlugin
        void execute() override
        {
            plugin->execute();
        }
    private:
        IPlugin* plugin;
        IoCPluginManager* deleter;
    };
};



#endif
