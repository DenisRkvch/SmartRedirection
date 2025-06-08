#ifndef INITIOCCONTAINERCOMMAND_H_INCLUDED
#define INITIOCCONTAINERCOMMAND_H_INCLUDED

#include "../ICommand.h"

class InitIoCContainerCommand : public ICommand {
public:
    void execute(void) override;
};


#endif // INITIOCCONTAINERCOMMAND_H_INCLUDED