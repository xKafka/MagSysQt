#ifndef SERIAL_PORT_READER_H
#define SERIAL_PORT_READER_H

#include <QSerialPortInfo>
#include <vector>
#include <string>

namespace serial_port_reader
{
    std::vector<std::string> get_available_ports()
    {
        std::vector<std::string> ret_val;

        foreach(const QSerialPortInfo &port, QSerialPortInfo::availablePorts())
            ret_val.emplace_back(port.portName().toStdString());

        return ret_val;
    }

}

#endif // SERIAL_PORT_READER_H
