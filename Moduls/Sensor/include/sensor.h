#ifndef SENSOR_H
#define SENSOR_H


#include <QObject>

#include <QThread>
#include <QObject>
#include <memory>

#include <Utils/include/module.h>
#include <Utils/include/command.h>

#include <Moduls/Serial/include/serial_settings.h>

#include "sensorworker.h"

class Sensor : public QObject
{
    Q_OBJECT

    std::string_view m_name { "sensor" };

    QThread m_thread{};
    SensorWorker *m_worker{};

    bool m_is_on_position{};

public:
    Sensor();
    ~Sensor() noexcept override;

    [[nodiscard]] inline auto name() const { return m_name; }

    [[nodiscard]] inline auto *worker() const { return m_worker; }

    bool do_magic(const Command &cmd);

    void read_cmd(const std::vector<std::string> &args);

    void show_cmd(const std::vector<std::string> &args);

    void change_cmd(const std::vector<std::string> &args);

    void open_cmd(const std::vector<std::string> &args);

    void close_cmd(const std::vector<std::string> &args);

    void load_cmd(const std::vector<std::string> &args);

};

#endif // SENSOR_H
