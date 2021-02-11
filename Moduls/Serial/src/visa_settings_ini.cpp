#include <QApplication>
#include <QString>
#include <Moduls/Serial/include/visa_settings_ini.h>

inline const std::string adress { "adress" };
inline const std::string name { "name" };
inline const std::string polarity { "polarity" };
inline const std::string port { "port" };
inline const std::string averaging { "averaging" };
inline const std::string range { "range" };

VISASettingsIni::VISASettingsIni(const std::string &name)
    : m_settings{},
      m_name{ name },
      m_mem_settings{ QApplication::applicationDirPath() + "/config/" + name.data() + ".ini", QSettings::IniFormat }
{
    read_settings();
}

std::string VISASettingsIni::read_value_from_init(const std::string &key) const
{
    return m_mem_settings.value(key.data()).toString().toStdString();
}

void VISASettingsIni::read_settings()
{
    m_settings.name = read_value_from_init(name);

    m_settings.adress = read_value_from_init(adress);

    m_settings.polarity = read_value_from_init(polarity);

    m_settings.averaging = read_value_from_init(averaging);

    m_settings.port = read_value_from_init(port);
}

std::string VISASettingsIni::print_current_settings() const
{
    std::string ret_val;

    ret_val += "{" + m_name + "}\n";
    ret_val += "<" + adress + ">............." + read_value_from_init(adress) + "\n";
    ret_val += "<" + name + ">.............." + read_value_from_init(name);
    ret_val += "<" + port + ">..............." + read_value_from_init(port) + "\n";
    ret_val += "<" + polarity + ">............" + read_value_from_init(polarity) + "\n";
    ret_val += "<" + averaging + ">........." + read_value_from_init(averaging) + "\n";
    ret_val += "<" + range + ">.............." + read_value_from_init(range) + "\n";

    return ret_val;
}

std::pair<std::string, std::string> VISASettingsIni::create_key_data_pair(std::string_view from)
{
    auto found = std::find_if(from.begin(), from.end(), [](const char val){ return val == '='; });

    std::string key(from.data(), std::distance(from.begin(), found));

    std::string value(found + 1, std::distance(found, from.end()));

    return { key, value };
};

void VISASettingsIni::find_and_change(std::string_view key, std::string_view value)
{
    auto change_in_ini_settings = [&]() { m_mem_settings.setValue(key.data(), value.data()); };

    if(key == adress)
        m_settings.adress = value;

    if(key == name)
        m_settings.name = value;

    if(key == polarity)
        m_settings.polarity = value;

    if(key == averaging)
        m_settings.averaging = value;

    if(key == port)
        m_settings.port = value;

    if(key == range)
        m_settings.range = value;

    change_in_ini_settings();
}

void VISASettingsIni::change_setting(const std::vector<std::string> &args)
{
    for(const auto &arg : args)
    {
        const auto map_key_val = create_key_data_pair(arg);

        find_and_change(map_key_val.first, map_key_val.second);
    }
}
