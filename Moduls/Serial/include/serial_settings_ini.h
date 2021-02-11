#ifndef SERIAL_SETTINGS_INI_H
#define SERIAL_SETTINGS_INI_H

#include <Moduls/Serial/include/serial_settings.h>

#include <QSettings>

class SerialSettingsIni
{
    SerialSettings m_settings{};
    const std::string m_name;
    QSettings m_mem_settings{};


    std::pair<std::string, std::string> create_key_data_pair(std::string_view from);

    std::string read_value_from_init(const std::string &key) const;

public:
    SerialSettingsIni(const std::string &name);

    std::string print_current_settings() const;

    inline auto &settings() const { return m_settings; }

    void read_settings();

public slots:
    void change_setting(const std::vector<std::string> &args);
};

#endif // SERIAL_SETTINGS_INI_H
