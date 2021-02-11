QT       += core gui serialport datavisualization 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES = $$files("*.cpp", true)

HEADERS = $$files("*.h", true)

FORMS = $$files("*.ui", true)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/Moduls/Sensor/extern/visa/lib/ -lvisa32

INCLUDEPATH += $$PWD/Moduls/Sensor/extern/visa/include
DEPENDPATH += $$PWD/Moduls/Sensor/extern/visa/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/Moduls/Sensor/extern/visa/lib/visa32.lib
