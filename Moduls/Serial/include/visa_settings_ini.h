#ifndef VISA_SETTINGS_INI_H
#define VISA_SETTINGS_INI_H

#include <Moduls/Serial/include/visa_settings.h>

#include <QSettings>

class VISASettingsIni
{
    VISASettings m_settings{};

    const std::string m_name;

    QSettings m_mem_settings{};

    std::pair<std::string, std::string> create_key_data_pair(std::string_view from);

    std::string read_value_from_init(const std::string &key) const;

public:
    VISASettingsIni(const std::string &name);

    std::string print_current_settings() const;

    inline auto &settings() const { return m_settings; }

    void read_settings();

    void find_and_change(std::string_view key, std::string_view value);

public slots:
    void change_setting(const std::vector<std::string> &args);
};

#endif // VISA_SETTINGS_INI_H
