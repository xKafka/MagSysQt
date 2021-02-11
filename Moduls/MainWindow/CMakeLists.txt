file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "Include/*.h")
file(GLOB_RECURSE forms "ui/*.ui")

qt5_wrap_ui(ui_wrapped ${forms})
qt5_wrap_cpp(cpp_wrapped ${headers})

add_library(main_window_module STATIC ${sources} ${ui_wrapped} ${cpp_wrapped})

target_include_directories(main_window_module PUBLIC Include PRIVATE src)

target_link_libraries(main_window_module Qt5::Widgets commander_module printer_module)