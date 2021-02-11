//
// Created by kafka on 2/7/2021.
//

#ifndef MESYS_ROOT_MODULE_SELECTOR_H
#define MESYS_ROOT_MODULE_SELECTOR_H

#include <Moduls/Printer/include/printer.h>
#include <Moduls/MainWindow/Include/mainwindow.h>
#include <Moduls/Sensor/include/sensor.h>
#include <Moduls/STLObjectMeasurement/stlobjectmeasurement.h>

class ModuleSelector : public QObject
{
    Q_OBJECT

    Printer m_printer{};

    MainWindow m_main_window{};

    Sensor m_sensor{};

    STLObjectMeasurement m_magsys{};

    std::string m_using_module{};

    bool m_is_using_selected{ false };

    bool want_use_variable(const std::string &cmd, const std::vector<std::string> &args);

    void dump(const std::string &what);

public:
    ModuleSelector();
    ~ModuleSelector();

    auto &printer() { return m_printer; }

    std::string_view do_magic() { return "printer je tu"; }

public slots:
    void choose_module(std::string_view cmd);

signals:
    void visualize(const Position &);
};


#endif //MESYS_ROOT_MODULE_SELECTOR_H
