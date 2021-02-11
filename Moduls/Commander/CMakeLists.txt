set(sources src/commander.cpp src/commandparser.cpp ../../Utils/include/command.h)

add_library(commander_module STATIC ${sources})

target_include_directories(commander_module PRIVATE src PUBLIC include)

target_link_libraries(commander_module Qt5::Widgets utils_module)
