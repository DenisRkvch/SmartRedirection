#ifndef IPLUGIN_H_INCLUDED
#define IPLUGIN_H_INCLUDED

class IPlugin
{
public:
	virtual ~IPlugin() = default;
	virtual void execute() = 0;
};

#endif