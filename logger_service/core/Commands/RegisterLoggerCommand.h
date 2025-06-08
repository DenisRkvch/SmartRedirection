#ifndef REGISTERLOGGERCOMAND_H
#define REGISTERLOGGERCOMAND_H

#include "../ICommand.h"

class RegisterLoggerCommand : public ICommand
{

public:
    void execute() override;
};

#endif // REGISTERLOGGERCOMAND_H
