#ifndef SERIAL_SETTINGS_H
#define SERIAL_SETTINGS_H

#include "serial_constants.h"
#include <utility>

struct SerialSettings
{
    template<typename Type>
    using sett_map = std::map<std::string_view, const Type>;

    std::string com{};
    sett_map<const QSerialPort::BaudRate>::const_iterator baud_rate{};
    sett_map<const QSerialPort::DataBits>::const_iterator data_bits{};
    sett_map<const QSerialPort::StopBits>::const_iterator stop_bits{};
    sett_map<const QSerialPort::FlowControl>::const_iterator flow_control{};
    sett_map<const QSerialPort::Parity>::const_iterator parity{};
};

#endif // SERIAL_SETTINGS_H
