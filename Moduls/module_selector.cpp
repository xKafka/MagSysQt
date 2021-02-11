//
// Created by kafka on 2/7/2021.
//
#include <Moduls/Commander/include/commandparser.h>

#include <Moduls/module_selector.h>

#include <QDebug>

constexpr const bool success { true };
constexpr const bool failed { false };

ModuleSelector::ModuleSelector()
{
    connect(&m_main_window, &MainWindow::command_signal, this, [&](const std::string cmd){  choose_module(cmd); });

    connect(m_printer.worker(), &PrinterWorker::dump, &m_main_window, &MainWindow::to_echo_write);

    connect(m_sensor.worker(), &SensorWorker::dump, &m_main_window, &MainWindow::to_echo_write);

    connect(m_magsys.worker(), &STLObjectMeasurementWorker::dump, &m_main_window, &MainWindow::to_echo_write);

    connect(m_printer.worker(), &PrinterWorker::visualize, &m_main_window, &MainWindow::visualize);

    connect(m_printer.worker(), &PrinterWorker::is_on_position, m_magsys.worker(), &STLObjectMeasurementWorker::printer_on_position);

    connect(m_sensor.worker(), &SensorWorker::new_data_available, m_magsys.worker(), &STLObjectMeasurementWorker::new_data_available);

    connect(m_magsys.worker(), &STLObjectMeasurementWorker::command, this, &ModuleSelector::choose_module);

    m_main_window.show();
}

ModuleSelector::~ModuleSelector() {}

void ModuleSelector::dump(const std::string &what)
{
    m_main_window.to_echo_write(what);
}

bool ModuleSelector::want_use_variable(const std::string &cmd, const std::vector<std::string> &args)
{
    if(m_is_using_selected && cmd == "var.clr")
    {
        m_is_using_selected = false;

        dump("{var} unused");

        return success;
    }

    if(!m_is_using_selected && cmd == "var.set")
    {
        if(args.empty())
        {
            dump("{var} keyword needs {arg: module_name}");

            return success;
        }
        else
        {
            m_using_module = args.front();
            m_is_using_selected = true;

            dump("{var} reserved for {" + args.front() + "}");

            return success;
        }
    }

    return failed;
}

void ModuleSelector::choose_module(std::string_view cmd) {

    auto parsed = parser::parse_cmd(cmd);

    auto choose_magic = [&](){

        if(parsed.module == m_printer.name())
        {
            if(!m_printer.do_magic(parsed))
                dump("wrong no such keys exits, for more info use { --help }");

            return success;
        }
        else if(parsed.module == m_main_window.name())
        {
            m_main_window.do_magic(parsed);

            return success;
        }
        else if(parsed.module == m_sensor.name())
        {
            m_sensor.do_magic(parsed);

            return success;
        }

        else if(parsed.module == m_magsys.name())
        {
            m_magsys.do_magic(parsed);

            return success;
        }

        return failed;
    };

    if(want_use_variable(parsed.module, parsed.args))
        return;

    if(m_is_using_selected && parsed.module == "var")
    {
        parsed.module = m_using_module;

        if(!choose_magic() && !m_is_using_selected)
            dump("{" + parsed.module + "}" + " such module does not exist");
    }
    else
    {
        if(!choose_magic() && !m_is_using_selected)
            dump("{" + parsed.module + "}" + " such module does not exist");
    }
}


