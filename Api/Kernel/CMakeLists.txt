file(GLOB_RECURSE files "src/*.cpp")

add_executable(mesys_kernel ${files})

target_include_directories(mesys_kernel PRIVATE src PUBLIC Include)

target_link_libraries(mesys_kernel main_window_module)