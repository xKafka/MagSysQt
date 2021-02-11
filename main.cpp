#include <Moduls/module_selector.h>
#include <QApplication>

#include <QDebug>

#include <Moduls/Sensor/include/visa_resource_manager.h>

#include <Moduls/Sensor/include/visa_device.h>

#include <Moduls/STLObjectMeasurement/positionfilereader.h>

int main(int argc, char *argv[])
{
    QApplication api(argc, argv);

    qRegisterMetaType<Position>("Position");

    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");

    qRegisterMetaType<std::string>("std::string");

    ModuleSelector selector;

    return api.exec();
}

