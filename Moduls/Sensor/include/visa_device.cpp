#include "visa_device.h"

#include <QDebug>

VISADevice::VISADevice()
{
    m_buffer.resize(buffer_size);
}
VISADevice::VISADevice(const VISASettings &settings)
    : m_settings { settings }
{
    m_buffer.resize(buffer_size);
}

VISADevice::~VISADevice()
{
    close();
}

SuccesDataType VISADevice::write_n_read(SCPI &&command)
{
    if(send_cmd(command))
    {
        const auto [data, success] = read();

       if(success)
            return { data, success };
    }

    return { m_buffer, false};
}

bool VISADevice::close()
{
    status = viClose(instrument) ==  VI_SUCCESS  && viClose(resource_manager) == VI_SUCCESS;

    return last_operation_success();
}

bool VISADevice::open()
{
    status = viOpenDefaultRM(&resource_manager);

    if(last_operation_success())
    {
        status = viOpen(resource_manager, m_settings.adress.data(), access_mode, time_out, &instrument);
    }

    return last_operation_success();
}

bool VISADevice::send_cmd(SCPI &command)
{
    status = viWrite(instrument, command.data(), command.size(), ViPUInt32 {});

    return last_operation_success();
}

bool VISADevice::send_cmd(SCPI &&command)
{
    status = viWrite(instrument, command.data(), command.size(), ViPUInt32 {});


    return last_operation_success();
}

SuccesDataType VISADevice::check_identity()
{
    return write_n_read(SCPI::identify());
}

bool VISADevice::set_attribute(Generic_NEMACC_Attribute attribute)
{
    status = viSetAttribute(instrument, attribute, time_out);

    return last_operation_success();
}

std::string &VISADevice::resize_buffer(const std::size_t toSize)
{
    if(m_buffer.size() == toSize)
        return m_buffer;
    else
        m_buffer.resize(toSize);

    return m_buffer;
}

SuccesDataType VISADevice::read()
{
    status = viRead(instrument, last_red_data, buffer_size, &last_data_size);

    m_buffer.resize(last_data_size);

    std::move(last_red_data, last_red_data + last_data_size, m_buffer.data());

    return { m_buffer, last_operation_success() };
}

SuccesDataType VISADevice::read_data()
{
    send_cmd(SCPI::clear());

    send_cmd(SCPI::reset());

    send_cmd(SCPI::set_range(m_settings.port, m_settings.range));

    send_cmd(SCPI::set_polarity(m_settings.port, m_settings.polarity));

    send_cmd(SCPI::averaging(m_settings.averaging));

    send_cmd(SCPI::measure_voltage(m_settings.port));

    return read();
}



