#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <vector>
#include <algorithm>
#include <Utils/include/command.h>
#include <Utils/include/position.h>

namespace parser {

    Command fill_command(std::string_view to_split, char with_what);

    Command parse_cmd(std::string_view cmd);

    Position from_std_string(const std::vector<std::string> &from);

    std::vector<std::string> string_splitter(std::string_view to_split, const char with_what);

};
#endif // COMMANDPARSER_H
