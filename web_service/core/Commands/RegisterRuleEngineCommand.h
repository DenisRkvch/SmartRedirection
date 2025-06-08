#ifndef REGISTERRULEENGINECOMMAND_H_INCLUDED
#define REGISTERRULEENGINECOMMAND_H_INCLUDED

#include "../ICommand.h"

class RegisterRuleEngineCommand : public ICommand {
public:
    void execute(void) override;
};


#endif // REGISTERRULEENGINECOMMAND_H_INCLUDED