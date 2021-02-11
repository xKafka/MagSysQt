//
// Created by kafka on 2/6/2021.
//

#ifndef MESYS_ROOT_COMMAND_H
#define MESYS_ROOT_COMMAND_H

#include <string>
#include <vector>

struct Command
{
    std::string module{};
    std::vector<std::string> keys{};
    std::vector<std::string> args{};

    Command() = default;
};

#endif //MESYS_ROOT_COMMAND_H
