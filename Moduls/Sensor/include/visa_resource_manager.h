#ifndef VISA_RESOURCE_MANAGER_H
#define VISA_RESOURCE_MANAGER_H

#include <string>
#include <utility>
#include <vector>

#include "visa_device.h"

class VISAResourceManager
{
    std::map<std::size_t, VISADevice> m_devices{};

    std::string m_attribute{};

    std::optional<VISADevice> get_device_on_adress(const char* adress);

public:
    VISAResourceManager(const std::string &attribute);

    enum Error
    {
        Success = 0,
        ResNotFound,
        ResourceManagerNotOpen,
        DeviceOpeningFault,
        Size
    };

    Error search_devices();

    auto &devices() const { return m_devices; }
};

#endif // VISA_RESOURCE_MANAGER_H
