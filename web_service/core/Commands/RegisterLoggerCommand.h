#ifndef REGISTERLOGERCOMMAND_H_INCLUDED
#define REGISTERLOGERCOMMAND_H_INCLUDED

#include "../ICommand.h"
#include "../logger/ILogger.h"
#include <iostream>

class RegisterLoggerCommand : public ICommand {
public:
    void execute(void) override;

};


#endif // REGISTERLOGERCOMMAND_H_INCLUDED