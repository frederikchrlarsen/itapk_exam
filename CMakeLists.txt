cmake_minimum_required(VERSION 3.9)
project(itapk_exam)

set(CMAKE_CXX_STANDARD 17)


find_package( Threads )
find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Found Boost! ${Boost_INCLUDE_DIRS}")
endif()



add_executable(itapk_exam
        main.cpp
        src/Sensor.cpp
        include/Sensor.h
        include/sensors/ImuSensor.h
        include/Distributor.h
        include/Subscriber.h
        src/Distributor.cpp
        include/SensorData.h
        include/sensors/UltraSonicSensor.h
        include/Subscriber.h
        include/Units.h
        src/DataPlotter.cpp
        include/DataPlotter.h
        include/SensorInfo.h
        src/Units.cpp
        src/UltraSonicSensor.cpp
        include/manipulateData.h
        src/manipulateData.cpp
        include/Regulator.h
        src/Regulator.cpp
        src/ImuSensor.cpp)

target_link_libraries(itapk_exam ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

if(WIN32)
    target_link_libraries(itapk_exam bcrypt.lib)
else()

endif()

target_include_directories(itapk_exam PRIVATE include include/sensors)
