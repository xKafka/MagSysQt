#ifndef VISA_DEVICE_H
#define VISA_DEVICE_H

#include <QObject>
#include <vector>
#include <optional>

#include "scpi.h"
#include <Moduls/Serial/include/visa_settings.h>

#include <visa/visa.h>
#include <visa/visatype.h>

using SuccesDataType = std::pair<std::string &, bool>;

class VISADevice
{
public :
    enum Generic_NEMACC_Attribute
    {
        InterfaceType = VI_ATTR_INTF_TYPE,
        BoardNumber = VI_ATTR_INTF_NUM,
        MinTimeoutValue = VI_ATTR_TMO_VALUE,
        HumanReadableText = VI_ATTR_INTF_INST_NAME
    };
private:

    using uLong = unsigned long;

    uLong time_out{ 5000 };
    uLong resource_manager{};
    uLong access_mode{ VI_NULL };
    uLong buffer_size{ 64 };
    uLong status{};
    uLong instrument{};
    uLong last_data_size{};

    VISASettings m_settings{};

    std::string m_buffer{};

    unsigned char last_red_data[8192];

    inline bool last_operation_success() const { return status == VI_SUCCESS; }

    std::string &resize_buffer(const std::size_t toSize);

    bool send_cmd(SCPI &command);

    bool send_cmd(SCPI &&command);

public:
    VISADevice();
    explicit VISADevice(const VISASettings &settings);
    ~VISADevice();

    bool open();

    SuccesDataType read();

    SuccesDataType read_data();

    SuccesDataType check_identity();

    inline auto &set(const VISASettings &settings) { m_settings = settings; return *this;}

    bool set_attribute(Generic_NEMACC_Attribute attribute);

    bool close();

    auto &settings() const { return m_settings; }

    SuccesDataType write_n_read(SCPI &&command);


signals:

};
#endif // VISA_DEVICE_H
