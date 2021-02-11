#ifndef VISA_SETTINGS_H
#define VISA_SETTINGS_H

#include <string>

struct VISASettings
{
    std::string name{};
    std::string adress{};
    std::string averaging{};
    std::string polarity{};
    std::string port{};
    std::string range{};
};

#endif // VISA_SETTINGS_H
