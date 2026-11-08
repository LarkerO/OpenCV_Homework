cmake_minimum_required(VERSION 4.4)
project(cpp_opencv_homework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

add_executable(cpp_opencv_homework main.cpp)

target_link_libraries(cpp_opencv_homework ${OpenCV_LIBS})
target_include_directories(cpp_opencv_homework PRIVATE ${OpenCV_INCLUDE_DIRS})