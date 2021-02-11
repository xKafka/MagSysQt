#include <Moduls/Printer/include/printer.h>
#include <Moduls/Printer/include/cmd_data_base.h>

#include <QDebug>

Printer::Printer()
    :   m_thread(this),
        m_worker(new PrinterWorker)
{
   worker()->moveToThread(&m_thread);

   connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);

   m_thread.start();
}
Printer::~Printer()
{
    m_thread.wait();
    m_thread.quit();
}

bool Printer::do_magic(const Command &cmd)
{
    for(const auto &key : cmd.keys)
    {
        if(key == "--move")
        {
            move_cmd(cmd.args);

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

        if(key == "--close_port")
        {
            close_cmd(cmd.args);

            return true;
        }

        return false;
    }

    return false;
}

void Printer::move_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "move_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Printer::show_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "show_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Printer::change_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "change_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Printer::open_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "open_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

void Printer::close_cmd(const std::vector<std::string> &args)
{
    QMetaObject::invokeMethod(m_worker, "close_cmd", Qt::AutoConnection, Q_ARG(const std::vector<std::string> &, args));
}

