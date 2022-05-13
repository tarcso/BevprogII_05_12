cmake_minimum_required(VERSION 3.22)
project(Autokolcsonzo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include_directories(graphicslib)
add_subdirectory(graphicslib)

add_compile_options("-Wall")

file(GLOB sources *.cpp)
add_executable(main ${sources})
target_link_libraries(main graphics)
