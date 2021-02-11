#include <QApplication>
#include <QString>
#include <Moduls/Serial/include/serial_settings_ini.h>

using map_pair = std::pair<std::string, std::string>;

inline const std::string com { "COM" };
inline const std::string baud_rate { "baud_rate" };
inline const std::string data_bits { "data_bits" };
inline const std::string stop_bits { "stop_bits" };
inline const std::string flow_control { "flow_control" };
inline const std::string parity { "parity" };

SerialSettingsIni::SerialSettingsIni(const std::string &name)
    : m_settings{},
      m_name{ name },
      m_mem_settings{ QApplication::applicationDirPath() + "/config/" + name.data() + ".ini", QSettings::IniFormat }
{
    read_settings();
}

std::string SerialSettingsIni::read_value_from_init(const std::string &key) const
{
    return m_mem_settings.value(key.data()).toString().toStdString();
}

void SerialSettingsIni::read_settings()
{
    m_settings.com = read_value_from_init(com);

    m_settings.baud_rate = serial_constants::baud_rate.find(read_value_from_init(baud_rate));

    m_settings.data_bits = serial_constants::data_bits.find(read_value_from_init(data_bits));

    m_settings.stop_bits = serial_constants::stop_bits.find(read_value_from_init(stop_bits));

    m_settings.flow_control = serial_constants::flow_control.find(read_value_from_init(flow_control));

    m_settings.parity = serial_constants::parity.find(read_value_from_init(parity));
}

std::string SerialSettingsIni::print_current_settings() const
{
    std::string ret_val;

    ret_val += "{" + m_name + "}\n";
    ret_val += "<" + com + ">....................{" + read_value_from_init(com) + "}\n";
    ret_val += "<" + baud_rate + ">..............{" + read_value_from_init(baud_rate) + "}\n";
    ret_val += "<" + data_bits + ">...............{" + read_value_from_init(data_bits) + "}\n";
    ret_val += "<" + stop_bits + ">...............{" + read_value_from_init(stop_bits) + "}\n";
    ret_val += "<" + flow_control + ">...........{" + read_value_from_init(flow_control) + "}\n";
    ret_val += "<" + parity + ">...................{" + read_value_from_init(parity) + "}\n";

    return ret_val;
}

map_pair SerialSettingsIni::create_key_data_pair(std::string_view from)
{
    auto found = std::find_if(from.begin(), from.end(), [](const char val){ return val == '='; });

    std::string key(from.data(), std::distance(from.begin(), found));

    std::string value(found + 1, std::distance(found, from.end()));

    return { key, value };
};

void SerialSettingsIni::change_setting(const std::vector<std::string> &args)
{
    auto find_and_change = [&](std::string_view key, std::string_view value)
    {
        auto change_in_ini_settings = [&]() { m_mem_settings.setValue(key.data(), value.data()); };

        if(key == com)
            m_settings.com = value;

        if(key == baud_rate)
            m_settings.baud_rate = serial_constants::baud_rate.find(value);

        else if(key == data_bits)
            m_settings.data_bits = serial_constants::data_bits.find(value);

        else if(key == stop_bits)
            m_settings.stop_bits = serial_constants::stop_bits.find(value);

        else if(key == flow_control)
            m_settings.flow_control = serial_constants::flow_control.find(value);

        else if(key == parity)
            m_settings.parity = serial_constants::parity.find(value);

        change_in_ini_settings();
    };

    for(const auto &arg : args)
    {
        const auto map_key_val = create_key_data_pair(arg);

        find_and_change(map_key_val.first, map_key_val.second);
    }
}



