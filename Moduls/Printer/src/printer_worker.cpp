#include <QDebug>
#include <Moduls/Printer/include/printer_worker.h>
#include <Moduls/Serial/include/serial_port_reader.h>
#include <Moduls/Printer/include/gcode_generator.h>
#include <Moduls/Commander/include/commandparser.h>

#include <cmath>
#include <QThread>
#include <QEventLoop>

PrinterWorker::PrinterWorker()
    : m_port{ this }
{    
    connect(&m_port, &QSerialPort::readyRead, this, &PrinterWorker::read_if_ready);
}

void PrinterWorker::read_if_ready()
{
    const auto red_data = m_port.readAll();

    m_last_data.reserve(red_data.size());

    std::move(red_data.begin(), red_data.end(), m_last_data.begin());
}

PrinterWorker::~PrinterWorker()
{
    close_port();
}

void PrinterWorker::show_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(arg == "ports")
            {
                show_available_ports();

                return;
            }
            else if(arg == "port")
            {
                show_port();

                return;
            }
            else if(arg == "settings")
            {
                show_settings();

                return;
            }
            else if(arg == "position")
            {
                show_position();

                return;
            }
        }
    });
}

void PrinterWorker::change_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(arg == "settings")
            {
                change_settings(args);

                return;
            }
        }
    });
}

void PrinterWorker::open_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(arg == "port")
            {
                open_port();

                return;
            }
        }
    });
}

void PrinterWorker::move_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        if(args.front() == "home")
        {
            move_home(args.at(1));
        }

        move(args);
    });
}

void PrinterWorker::close_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(arg == "port")
            {
                close_port();

                return;
            }
        }
    });
}

void PrinterWorker::move_home(const std::string &arg)
{
    const auto args_is_valit = [&arg]()
    {
        return arg == "X" || arg == "Z" || arg == "Y" || arg == "all";
    };

    if(!args_is_valit())
        emit dump("{printer} arguments are not valid use <home x/y/z/all>");
    else
    {
        std::string g_cmd("G28" + arg + "\n");

        m_port.write(g_cmd.data(), g_cmd.length());

        m_position = {0.0 ,0.0, 0.0};
    }

    emit is_on_position(m_position);

    emit visualize(m_position);
}

inline void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

void PrinterWorker::show_move_trajectory(const Position &prev, const Position &next)
{
    bool x_bigger = next.getX() > prev.getX();
    bool y_bigger = next.getY() > prev.getY();
    bool z_bigger = next.getZ() > prev.getZ();

    bool x_neg = !x_bigger;
    bool y_neg = !y_bigger;
    bool z_neg = !z_bigger;

    bool done_x{false}, done_y{false}, done_z{false};

    Position to_emit = prev;

    auto do_this_x = x_bigger ? [](Position &wat, const double step){ wat.setX(wat.getX() + step); } : [](Position &wat, const double step){ wat.setX(wat.getX() - step); };

    auto do_this_y = y_bigger ? [](Position &wat, const double step){ wat.setY(wat.getY() + step); } : [](Position &wat, const double step){ wat.setY(wat.getY() - step); };

    auto do_this_z = z_bigger ? [](Position &wat, const double step){ wat.setZ(wat.getZ() + step); } : [](Position &wat, const double step){ wat.setZ(wat.getZ() - step); };

    while(!done_x || !done_y || !done_z)
    {
        int del = 0;

        x_bigger = next.getX() > to_emit.getX();
        y_bigger = next.getY() > to_emit.getY();
        z_bigger = next.getZ() > to_emit.getZ();

        if(x_bigger != x_neg)
        {
            do_this_x(to_emit, 0.1);

            ++del;
        }
        else
            done_x = true;

        if(y_bigger != y_neg)
        {
            do_this_y(to_emit, 0.1);

            ++del;
        }
        else
            done_y = true;

        if(z_bigger != z_neg)
        {
            do_this_z(to_emit, 0.1);

            del += 11;
        }
        else
            done_z = true;

        delay(del);

        emit visualize(to_emit);
    }

    emit visualize(next);
}

void PrinterWorker::move(const std::vector<std::string> &where)
{
    m_port.flush();

    auto prev = m_position;

    m_position = parser::from_std_string(where);

    const auto g_command = g_command_generator::generate_position(m_position);

    m_port.write(g_command.data(), g_command.length());

    show_position();

    show_move_trajectory(prev, m_position);

    delay(500);

    emit is_on_position(m_position);
}

void PrinterWorker::change_settings(const std::vector<std::string> &args)
{
    m_settings.change_setting(args);

    emit dump("{printer} settings changed");
}

void PrinterWorker::show_settings()
{
    emit dump(m_settings.print_current_settings());
}

void PrinterWorker::show_port()
{
    emit dump("{printer} port {" + m_settings.settings().com + "}");
}

void PrinterWorker::show_available_ports()
{
    const auto available_ports = serial_port_reader::get_available_ports();

    if(available_ports.empty())
    {
        emit dump("{printer} no available ports");

        return;
    }

    std::string dump_str;

    for(const auto &port : serial_port_reader::get_available_ports())
        dump_str += "{" + port + "} ";

    emit dump(dump_str);
}

void PrinterWorker::show_position()
{
    const auto create_dump = [&]()
    {
        std::string out;

        out += "{ " + std::to_string(m_position.getX()) + " }";
        out += "{ " + std::to_string(m_position.getY()) + " }";
        out += "{ " + std::to_string(m_position.getZ()) + " }";

        return "{printer} {X, Y, Z} " + out;
    };

    emit dump(create_dump());
}

void PrinterWorker::open_port()
{
    m_settings.read_settings();

    const auto &set = m_settings.settings();

    m_port.setPortName(set.com.data());
    m_port.setBaudRate(set.baud_rate->second);
    m_port.setDataBits(set.data_bits->second);
    m_port.setParity(set.parity->second);
    m_port.setStopBits(set.stop_bits->second);
    m_port.setFlowControl(set.flow_control->second);

    if(!m_port.isOpen())
    {
        if(m_port.open(QSerialPort::ReadWrite))
        {
            emit dump("{printer} port {""" + set.com + "} is opened");
        }
    }
}

void PrinterWorker::close_port()
{
    m_port.close();

    emit dump("{printer} port {" + m_settings.settings().com + "} has been closed");
}

void PrinterWorker::is_ready()
{
    emit dump(m_printer_ready ? "ready" : "not ready");
}

