#include <Moduls/Sensor/include/sensorworker.h>

#include <QString>

SensorWorker::SensorWorker(QObject *parent)
    : QObject(parent)
{
    m_device.set(m_settings.settings());
}

void SensorWorker::show_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(arg == "settings")
            {
                show_settings();

                return;
            }
            if(arg == "identity")
            {
                show_indentity();

                return;
            }
        }
    });
}

void SensorWorker::open_cmd(const std::vector<std::string> &args)
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

void SensorWorker::change_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(arg == "resource")
            {
                change_resource(args);

                return;
            }
            if(arg == "settings")
            {
                change_settings(args);

                return;
            }
        }
    });
}

void SensorWorker::read_cmd(const std::vector<std::string> &args)
{
    parse_cmd(args, [&]()
    {
        for(const auto &arg : args)
        {
            if(arg == "volt")
            {
                read(args);

                return;
            }
        }
    });
}

void SensorWorker::load_cmd([[maybe_unused]] const std::vector<std::string> &args)
{
    auto create_dump = [&]()
    {
        for(const auto &[index, device] : m_resource_manager.devices())
        {
            emit dump(  "{index} {"                 + std::to_string(index) +
                        "}\n{VISA alias} "          + device.settings().adress +
                        "\n{Manufacturer name} "    + device.settings().name);
        }
    };

    auto response = m_resource_manager.search_devices();

    switch(response)
    {
    case VISAResourceManager::Error::DeviceOpeningFault : emit dump("{sensor} could not open the device, check {sensor} connection"); break;
    case VISAResourceManager::Error::ResNotFound : emit dump("{sensor} VISA resurces could not be found"); break;
    case VISAResourceManager::Error::ResourceManagerNotOpen : emit dump("{sensor} VISA resoure manager could not be opened, check {sensor} connection"); break;
    case VISAResourceManager::Error::Success : create_dump(); break;

    default: return;
    }
}

void SensorWorker::close_cmd(const std::vector<std::string> &args)
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
void SensorWorker::change_settings(const std::vector<std::string> &args)
{
    m_settings.change_setting(args);

    emit dump("{sensor} settings changed");
}

void SensorWorker::change_resource(const std::vector<std::string> &args)
{
    auto is_number = [](const std::string &line) -> const bool
    {
        return !line.empty() && std::find_if(line.begin(),
            line.end(), [](unsigned char c) { return !std::isdigit(c); }) == line.end();
    };

    if(m_resource_manager.devices().empty())
    {
        emit dump("{sensor} no resoures loaded");

        return;
    }

    for(const auto &arg : args)
    {
        if(is_number(arg))
        {
            auto index = std::atoi(arg.data());

            if(static_cast<unsigned int>(index) >= m_resource_manager.devices().size())
            {
                emit dump("{sensor} no such resource loaded");

                return;
            }

            auto found = m_resource_manager.devices().find(index);

            m_settings.find_and_change("name", found->second.settings().name);
            m_settings.find_and_change("adress", found->second.settings().adress);
        }
    }

    emit dump("{sensor} resources changed");
}

void SensorWorker::show_settings()
{
    emit dump(m_settings.print_current_settings());
}

void SensorWorker::show_port()
{
    show_settings();
}

void SensorWorker::show_indentity()
{
    auto [data, success] = m_device.check_identity();

    emit dump(data);
}

void SensorWorker::open_port()
{
    if(m_device.open())
        emit dump("{sensor} device is opened");
    else
        emit dump("{sensor} device could not be opened");
}

void SensorWorker::close_port()
{
    m_device.close();
}

void SensorWorker::is_ready()
{

}

void SensorWorker::read(const std::vector<std::string> &args)
{
    auto is_number = [](const std::string &line) -> const bool
    {
        return !line.empty() && std::find_if(line.begin(),
            line.end(), [](unsigned char c) { return !std::isdigit(c); }) == line.end();
    };

    std::vector<std::string> ret_val;

    for(const auto &arg : args)
    {
        if(is_number(arg))
        {
            auto number_of_samples = std::atoi(arg.data());

            while(number_of_samples--)
            {
                auto [data, success] = m_device.read_data();

                if(success)
                {
                    emit dump("{sensor} " + data);

                    ret_val.push_back(std::move(data));
                }
            }
        }
    }

    emit new_data_available(ret_val);
}


