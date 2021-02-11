#ifndef SENSORWORKER_H
#define SENSORWORKER_H

#include <QDebug>

#include <Moduls/Serial/include/visa_settings_ini.h>

#include "visa_device.h"
#include "visa_resource_manager.h"

class SensorWorker : public QObject
{
    Q_OBJECT

    VISADevice m_device{};

    VISAResourceManager m_resource_manager{ "?*INSTR" };

    VISASettingsIni m_settings{ "sensor" };

    template<typename CmdRecognizer>
    void parse_cmd(const std::vector<std::string> &args, CmdRecognizer recognizer)
    {
        if(args.empty())
            emit dump("{sensor} no such commands allowed");
        else
        {
            recognizer();
        }
    }
    void change_resource(const std::vector<std::string> &args);

    void change_settings(const std::vector<std::string> &args);

    void show_available_ports();                                            //from show cmd

    void show_settings();                                                   //from show cmd

    void show_port();                                                        //from show cmd

    void show_indentity();                                                        //from show cmd

    void open_port();                                                       //from open cmd

    void close_port();

    void is_ready();

    void read(const std::vector<std::string> &args);

public:
    explicit SensorWorker(QObject *parent = nullptr);

public slots:
    void change_cmd(const std::vector<std::string> &args);

    void show_cmd(const std::vector<std::string> &args);

    void open_cmd(const std::vector<std::string> &args);

    void load_cmd(const std::vector<std::string> &args);

    void close_cmd(const std::vector<std::string> &args);

    void read_cmd(const std::vector<std::string> &args);


signals:
    void dump(const std::string &what);
    void new_data_available(const std::vector<std::string> &);
};

#endif // SENSORWORKER_H
