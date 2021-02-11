#ifndef MODULE_H
#define MODULE_H

#include "command.h"

class Module
{
public:
    virtual void do_magic(const Command &data) = 0;
    virtual ~Module() = default;
};

#endif // MODULE_H
