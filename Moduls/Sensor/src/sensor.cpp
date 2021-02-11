#include <Moduls/Sensor/include/sensor.h>

Sensor::Sensor()
    :   m_thread(this),
        m_worker(new SensorWorker)
{
   worker()->moveToThread(&m_thread);

   connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);

   m_thread.start();
}
Sensor::~Sensor()
{
    m_thread.wait();
    m_thread.quit();
}

bool Sensor::do_magic(const Command &cmd)
{
    for(const auto &key : cmd.keys)
    {
        if(key == "--read")
        {
            read_cmd(cmd.args);

            return true;
        }

        if(key == "--change")
        {
            change_cmd(cmd.args);

            return true;
        }

        if(key == "--show")
        {
            show_cmd(cmd.args);

            return true;
        }

        if(key == "--open")
        {
            open_cmd(cmd.args);

            return true;
        }

        if(key == "--load")
        {
            load_cmd(cmd.args);

            return true;
        }

        if(key == "--close")
        {
            close_cmd(cmd.args);

            return true;
        }

        return false;
    }

    return false;
}

void Sensor::show_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "show_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Sensor::change_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "change_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Sensor::read_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "read_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Sensor::load_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "load_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Sensor::open_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "open_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Sensor::close_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "close_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}
