set(sources src/sensor.cpp)

find_package(Qt5 COMPONENTS SerialPort REQUIRED)

add_library(sensor_module STATIC ${sources})

target_include_directories(sensor_module PRIVATE src PUBLIC include)

target_link_libraries(sensor_module PRIVATE Qt5::SerialPort )