#include "stlobjectmeasurementworker.h"

#include <Moduls/Commander/include/commandparser.h>

#include <QDebug>
#include <QTimer>
#include <QEventLoop>

constexpr std::string_view samples_per_step { "sps" };
constexpr std::string_view on_position_wait { "wait" };

STLObjectMeasurementWorker::STLObjectMeasurementWorker(QObject *parent)
    : QObject(parent)
{

}

void STLObjectMeasurementWorker::run_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        run(args);
    });
}

void STLObjectMeasurementWorker::show_cmd([[maybe_unused]]const std::vector<std::string> &args)
{

}

void STLObjectMeasurementWorker::stop_cmd(const std::vector<std::string> &args)
{

}

inline void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

void STLObjectMeasurementWorker::printer_on_position(const Position &position)
{
    if(m_is_running && m_steps != -1)
    {        
        emit command("sensor --read volt " + m_config.samples_per_step);
    }
    else
    {
        m_printer_position = position;

        m_is_running = false;
    }
}

void STLObjectMeasurementWorker::new_data_available(const std::vector<std::string> &data)
{
    if(m_is_running && m_steps == 0)
    {
        emit dump("{magsys} measurement successfully done");

        m_is_running = false;

        return;
    }

    if(m_is_running)
    {
        Position next_position = parser::from_std_string(parser::string_splitter(m_position_reader.get_next_str(), ' '));

        next_position += m_printer_position;

        emit command("printer --move " + std::to_string(next_position.getX()) + " " + std::to_string(next_position.getY()) + " " + std::to_string(next_position.getZ()));

        --m_steps;
    }
}

void STLObjectMeasurementWorker::load_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(*arg.begin() == '"' && *(arg.end() - 1) == '"')
            {
                load_file(std::string(arg.begin() + 1, arg.end() - 1));

                 return;
            }
        }
    });
}

void STLObjectMeasurementWorker::run(const std::vector<std::string> &args)
{
    for(const auto &arg : args)
    {
        if(auto found = arg.find(on_position_wait.data()); found != std::string::npos)
        {
            m_config.on_position_delay = std::string(arg.begin() + found + on_position_wait.size() + 1, arg.end());
        }
        if(auto found = arg.find(samples_per_step.data()); found != std::string::npos)
        {
            m_config.samples_per_step = std::string(arg.begin() + found + samples_per_step.size() + 1, arg.end());
        }
    }

    m_steps = m_position_reader.count_lines();

    m_is_running = true;

    printer_on_position(m_printer_position);
}

void STLObjectMeasurementWorker::load_file(const std::string &args)
{
    m_position_reader.set_adress(args);

    if(m_position_reader.open())
        emit dump("{magsys} file loaded successfully");
    else
        emit dump("{magsys} could not open file");
}
