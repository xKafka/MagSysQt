#include "visa_resource_manager.h"

#include <QDebug>

VISAResourceManager::VISAResourceManager(const std::string &attribute)
    : m_attribute{ attribute }
{
}

VISAResourceManager::Error VISAResourceManager::search_devices()
{
    ViStatus status;

    auto not_success = [&status](){ return status < VI_SUCCESS; };

    ViChar desc[VI_FIND_BUFLEN];
    ViSession defaultRM;
    ViUInt32 numInstrs;
    ViFindList fList;

    status = viOpenDefaultRM(&defaultRM);

    if(not_success())
        return VISAResourceManager::Error::ResourceManagerNotOpen;

    status = viFindRsrc(defaultRM, m_attribute.data(), &fList, &numInstrs, desc);

    if(not_success())
        return VISAResourceManager::Error::ResNotFound;

    while(numInstrs--)
    {
       auto device = get_device_on_adress(desc);

       if(!device.has_value())
       {
           return VISAResourceManager::Error::DeviceOpeningFault;
       }
       else
       {
           m_devices.emplace(numInstrs, device.value());
       }
    }

    return VISAResourceManager::Error::Success;
}

std::optional<VISADevice> VISAResourceManager::get_device_on_adress(const char* adress)
{
    VISASettings settings{};

    settings.adress = adress;

    VISADevice ret_val{ settings };

    if(ret_val.open())
    {
        const auto [identity, success] = ret_val.check_identity();

        if(success)
        {
            settings.name = identity;

            return std::make_optional<VISADevice>(settings);
        }
    }

    return std::nullopt;
}


