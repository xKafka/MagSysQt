#ifndef SERIAL_CONSTANTS_H
#define SERIAL_CONSTANTS_H

#include <string_view>
#include <QSerialPort>
#include <map>

namespace serial_constants
{
    inline const std::map<std::string_view, const QSerialPort::BaudRate> baud_rate{ {"9600",   QSerialPort::Baud9600},
                                                                                    {"19200",  QSerialPort::Baud19200},
                                                                                    {"38400",  QSerialPort::Baud38400},
                                                                                    {"57600",  QSerialPort::Baud57600},
                                                                                    {"115200", QSerialPort::Baud115200}
    };

    inline const std::map<std::string_view, const QSerialPort::DataBits> data_bits{ {"5", QSerialPort::Data5},
                                                                                    {"6", QSerialPort::Data6},
                                                                                    {"7", QSerialPort::Data7},
                                                                                    {"8", QSerialPort::Data8}
    };

    inline const std::map<std::string_view, const QSerialPort::StopBits> stop_bits{ {"1",   QSerialPort::OneStop},
                                                                                    {"1.5", QSerialPort::OneAndHalfStop},
                                                                                    {"2",   QSerialPort::TwoStop}
    };

    inline const std::map<std::string_view, const QSerialPort::FlowControl> flow_control{   { "None", QSerialPort::NoFlowControl },
                                                                                            { "RST/CTS", QSerialPort::HardwareControl },
                                                                                            { "XON/XOFF", QSerialPort::SoftwareControl }
    };

    inline const std::map<std::string_view, const QSerialPort::Parity> parity{{"None",  QSerialPort::NoParity},
                                                                              {"Even",  QSerialPort::EvenParity},
                                                                              {"Odd",   QSerialPort::OddParity},
                                                                              {"Mark",  QSerialPort::MarkParity},
                                                                              {"Space", QSerialPort::SpaceParity}
    };
};

#endif // SERIAL_CONSTANTS_H
