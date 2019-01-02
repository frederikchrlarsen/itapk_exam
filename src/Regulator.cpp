//
// Created by Taise on 29/12/2018.
//

#include <Regulator.h>

#include "Regulator.h"

apk::Regulator::Regulator(int regulateRateHZ) {
    regulateRateHZ_ = 1000/regulateRateHZ;
    std::cout << "Regulating with " << regulateRateHZ_ << "ms." << std::endl;
}

apk::Regulator::~Regulator() {
    running_ = false;
    boost::mutex::scoped_lock lock(threadMut_);
}

void apk::Regulator::controlLoop(){
    try {
        boost::mutex::scoped_lock lock(threadMut_);

        while (running_) {
            auto start = std::chrono::high_resolution_clock::now();
            doAdvancedRegulationAlgorithms();

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << "Time elapsed: " << diff.count() << "s" << std::endl;
            auto sleepTime = std::chrono::milliseconds(regulateRateHZ_) - diff;

            if (sleepTime.count() < 0) {
                throw RegulatorFailure();
            }
            std::this_thread::sleep_for(sleepTime);
        }
    }
    catch (RegulatorFailure& e){
        std::cout << e.what();
        throw;
    }
}

void apk::Regulator::imuSensorSignal(Imu::ReturnType data){
    imuData = data;
}

void apk::Regulator::ultraSonicSensorSignal(UltraSonicSensor::ReturnType data){
    ultraSonicData = data;
}

void apk::Regulator::doAdvancedRegulationAlgorithms(){
    std::cout << "Got data Length: " << ultraSonicData << " and imu: " << imuData << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

