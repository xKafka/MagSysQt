#ifndef POSITIONFILEREADER_H
#define POSITIONFILEREADER_H

#include <fstream>
#include <memory>

#include <Utils/include/position.h>

class PositionFileReader
{
    std::unique_ptr<std::fstream> m_file{};

    std::string m_adress{};

    Position parse_line(const std::string &line);

public:
    PositionFileReader();

    inline void set_adress(const std::string adress) { m_adress = adress; }

    Position get_next_position();

    bool open();

    std::size_t count_lines();

    std::string get_next_str();

};

#endif // POSITIONFILEREADER_H
