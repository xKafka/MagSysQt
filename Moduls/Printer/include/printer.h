//
// Created by kafka on 2/6/2021.
//

#ifndef MESYS_ROOT_PRINTER_H
#define MESYS_ROOT_PRINTER_H

#include <QObject>

#include <QThread>
#include <QObject>
#include <memory>

#include <Utils/include/module.h>
#include <Utils/include/command.h>

#include <Moduls/Serial/include/serial_settings.h>

#include "printer_worker.h"

class Printer : public QObject
{
    Q_OBJECT

    std::string_view m_name { "printer" };

    QThread m_thread{};
    PrinterWorker *m_worker{};

    bool m_is_on_position{};

public:
    Printer();
    ~Printer() noexcept override;

    [[nodiscard]] inline auto name() const { return m_name; }

    [[nodiscard]] inline auto *worker() const { return m_worker; }


    bool do_magic(const Command &cmd);

    void change_cmd(const std::vector<std::string> &args);

    void show_cmd(const std::vector<std::string> &args);

    void move_cmd(const std::vector<std::string> &args);

    void open_cmd(const std::vector<std::string> &args);

    void close_cmd(const std::vector<std::string> &args);

    void close_port();

};

#endif //MESYS_ROOT_PRINTER_H
