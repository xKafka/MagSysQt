#include <Moduls/Commander/include/commandparser.h>

constexpr std::string_view key_char { "--" };

Command parser::parse_cmd(std::string_view cmd)
{
    constexpr const char splitter{ ' ' };

    return fill_command(cmd, splitter);
}

std::vector<std::string> parser::string_splitter(std::string_view to_split, const char with_what)
{
    std::vector<std::string> ret_val;

    static auto const isCharComparator = [with_what](const char letter){ return letter == with_what; };

    auto finder = to_split.begin();

    while(finder != to_split.end())
    {
        auto const beg = std::find_if_not(finder, to_split.end(), isCharComparator);
        auto const end = std::find_if(beg, to_split.end(), isCharComparator);

        if(beg != end)
        {
            ret_val.emplace_back(std::string(beg, std::distance(beg, end)));
        }

        finder = end;
    }

    return ret_val;
}

Command parser::fill_command(std::string_view to_split, const char with_what)
{
    Command ret_val;

    for(const auto &cmd : parser::string_splitter(to_split, with_what))
    {
        if(ret_val.module.empty())
        {
            ret_val.module = cmd;

            continue;
        }

        if(cmd.find(key_char) == std::string::npos)
            ret_val.args.emplace_back(cmd);
        else
            ret_val.keys.emplace_back(cmd);
    }

    return ret_val;
}

Position parser::from_std_string(const std::vector<std::string> &from)
{
    std::vector<double> m_result;
    m_result.reserve(Position::Size);

    for(const auto &pos_str : from)
        m_result.emplace_back(std::atof(pos_str.data()));

    return { m_result[Position::X], m_result[Position::Y], m_result[Position::Z] };
}


