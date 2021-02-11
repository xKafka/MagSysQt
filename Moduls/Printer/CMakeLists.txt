set(sources src/printer.cpp src/printer_worker.cpp include/printer.h include/printer_worker.h)

add_library(printer_module STATIC ${sources})

target_include_directories(printer_module PRIVATE src PUBLIC include)

target_link_libraries(printer_module Qt5::Core utils_module serial_module)