//
// Created by frederik on 12/29/18.
//

#include "DataPlotter.h"


void apk::DataPlotter::addImuData(float data) noexcept(false){
    if(imuData_.size() > MAX_SIZE){
        throw DataPlotter::DataOverflow();
    }
    imuData_.push_back(data);
}

  apk::DataPlotter::imuBuffer* apk::DataPlotter::getImuData(){
    return &imuData_;
}

void apk::DataPlotter::ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) {

    std::cout << "Got data: " << data.meters() << "m" << std::endl;

    /*
    addImuData(data);

    std::cout << *this << std::endl;
    */
}

void apk::DataPlotter::imuSensorSignal(UltraSonicSensor::ReturnType data) {

}
