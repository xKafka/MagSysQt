//
// Created by kafka on 2/7/2021.
//

#ifndef MESYS_ROOT_PRINTER_WORKER_H
#define MESYS_ROOT_PRINTER_WORKER_H

#include <QObject>

#include <Utils/include/position.h>
#include <Moduls/Serial/include/serial_settings_ini.h>
#include <QTimer>

class PrinterWorker : public QObject
{
    Q_OBJECT

    QSerialPort m_port{};
    SerialSettingsIni m_settings{ "printer" };

    Position m_position{ 0.0, 0.0, 0.0 };

    bool m_printer_ready{ false };

    void change_settings(const std::vector<std::string> &args);             //from change cmd

    void show_available_ports();                                            //from show cmd

    void show_settings();                                                   //from show cmd

    void show_port();                                                        //from show cmd

    void show_position();

    void open_port();                                                       //from open cmd

    void close_port();

    void is_ready();

    void read_if_ready();

    void show_move_trajectory(const Position &prev, const Position &next);

    void move_home(const std::string &arg);

    void move(const std::vector<std::string> &where);

    Position to_Position(const std::vector<std::string> &where);

    template<typename CmdRecognizer>
    void parse_cmd(const std::vector<std::string> &args, CmdRecognizer recognizer)
    {
        if(args.empty())
            emit dump("{printer} no such commands allowed");
        else
        {
            recognizer();
        }
    }

public:
    PrinterWorker();
    ~PrinterWorker();

    std::string m_last_data{};

public slots:

    void move_cmd(const std::vector<std::string> &args);

    void change_cmd(const std::vector<std::string> &args);

    void show_cmd(const std::vector<std::string> &args);

    void open_cmd(const std::vector<std::string> &args);

    void close_cmd(const std::vector<std::string> &args);


signals:
    void dump(const std::string &);
    void is_on_position(const Position &);


    void visualize(const Position &);
};

#endif //MESYS_ROOT_PRINTER_WORKER_H
