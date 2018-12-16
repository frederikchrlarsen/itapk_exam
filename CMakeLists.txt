cmake_minimum_required(VERSION 3.9)
project(itapk_exam)

set(CMAKE_CXX_STANDARD 11)

find_package( Threads )

add_executable(itapk_exam main.cpp src/Sensor.cpp include/Sensor.h include/sensors/Imu.h)

target_link_libraries(itapk_exam ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(itapk_exam PRIVATE include include/sensors )
