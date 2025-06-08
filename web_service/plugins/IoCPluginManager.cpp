#include "IoCPluginManager.h"
#include "plugin_api_dll.h"


IoCPluginManager::IoCPluginManager(IIoCContainer* ioc) : ioc_container(ioc)
{
}

IoCPluginManager::~IoCPluginManager()
{
    for ( auto& [plug, handle] : open_plugins) {

        if (plug) { // удалить объект если еще не удален
            if (handle) {
                auto destructor = reinterpret_cast<void(*)(IPlugin*)>(GetProcAddress(handle, "destroy_plugin_object"));
                if (destructor) {
                    destructor(plug);
                }
                else {
                    delete plug;
                }
            }
            else {
                delete plug;
            }
        }

        if (handle) { // закрыть dll
            FreeLibrary(handle);         
        }

        
    }
    IoC::Resolve<ILogger*>("Logger")->log("ALL PLUGINS CLOSED \n");
}

IPlugin* IoCPluginManager::loadPlugin(const std::string& path)
{
    HMODULE handle = LoadLibraryA(path.c_str());
    if (!handle) {
        throw PluginConnectionException(
            "failed to load DLL: " + path +
            ", error: " + std::to_string(GetLastError())
        );
    }
    auto factory = reinterpret_cast<IPlugin * (*)()>(GetProcAddress(handle, "create_plugin_object"));
    if (!factory) {
        throw PluginConnectionException("api function create_plugin_object not found");
    }

    auto ioc_bind = reinterpret_cast<void(*)(IIoCContainer*)>(GetProcAddress(handle, "plugin_connect_ioc"));
    if (!ioc_bind) {
        IoC::Resolve<ILogger*>("Logger")->log("plugin does not support ioc binding \n");
    }
    else {
        ioc_bind(ioc_container);
    }
    
    IPlugin* plugin = factory();
    if (!plugin) {
        throw PluginConnectionException("plugin creation failed");
    }
    return new DestructiblePluginWrapper(this, plugin);
}



void IoCPluginManager::deletePlugin(IPlugin* plug)
{

    auto it = open_plugins.find(plug);
    if (it == open_plugins.end()) {
        delete plug; // Удаление статического объекта
        return;
    }

    HMODULE handle = it->second;
    open_plugins.erase(it);

    if (handle) {
        auto destructor = reinterpret_cast<void(*)(IPlugin*)>(GetProcAddress(handle, "destroy_plugin_object"));
        if (destructor) {
            destructor(plug);
            return;
        }
    }    
    
    throw PluginConnectionException("destroy_plugin_object function not found");
    
}
