cmake_minimum_required(VERSION 3.25)
project(hik_camera)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

add_executable(hik_camera HikCam.cpp)
target_link_libraries(hik_camera ${OpenCV_LIBS})
