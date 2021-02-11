add_library(serial_module INTERFACE)

find_package(Qt5 COMPONENTS SerialPort REQUIRED)

target_include_directories(serial_module INTERFACE include)

target_link_libraries(serial_module INTERFACE Qt5::SerialPort)

