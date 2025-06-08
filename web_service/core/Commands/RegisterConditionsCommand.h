#ifndef REGISTERCONDITIONSCOMMAND_H_INCLUDED
#define REGISTERCONDITIONSCOMMAND_H_INCLUDED

#include "../ICommand.h"

class RegisterConditionsCommand : public ICommand {
public:
    void execute(void) override;
};


#endif // REGISTERCONDITIONSCOMMAND_H_INCLUDED