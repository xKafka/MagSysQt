#include "positionfilereader.h"

#include <Moduls/Commander/include/commandparser.h>

#include <QDebug>

PositionFileReader::PositionFileReader()
    : m_file{ std::make_unique<std::fstream>() }
{

}

bool PositionFileReader::open()
{
    m_file->open(m_adress.data(), std::ios::in);

    return m_file->is_open();
}

Position PositionFileReader::get_next_position()
{
    return parse_line(get_next_str());
}

Position PositionFileReader::parse_line(const std::string &line)
{
    return parser::from_std_string(parser::string_splitter(line, ' '));
}

std::string PositionFileReader::get_next_str()
{
    std::string ret_val;

    std::getline(*m_file, ret_val);

    return ret_val;
}

std::size_t PositionFileReader::count_lines()
{
    std::size_t lines = 0;

    for(std::string line; std::getline(*m_file,line); ++lines);

    m_file->clear();
    m_file->seekg (0, std::ios::beg);

    return lines;
}

