//
// Created by Taise on 29/12/2018.
//

#include "Regulator.h"

apk::Regulator::Regulator() {

}

void apk::Regulator::controlLoop(){
    while(running_) {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Got data Length: " << ultraSonicData << " and imu: " << imuData << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;

        std::cout << "Time elapsed: " << diff.count() << "s" << std::endl;
        //std::this_thread::sleep_for(50ms);
    }
}

void apk::Regulator::imuSensorSignal(Imu::ReturnType data){
    imuData = data;
}

void apk::Regulator::ultraSonicSensorSignal(UltraSonicSensor::ReturnType data){
    ultraSonicData = data;
}

