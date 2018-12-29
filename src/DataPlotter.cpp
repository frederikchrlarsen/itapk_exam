//
// Created by frederik on 12/29/18.
//

#include <DataPlotter.h>

#include "DataPlotter.h"

void apk::DataPlotter::dataCallbackImu(const float data) {

    //std::cout << "Subscriber: " << boost::uuids::to_string(this->getId()) << "got data: " << data << std::endl;
    addImuData(data);

    std::cout << *this << std::endl;
}

void apk::DataPlotter::dataCallbackUSS(float data) {

}

void apk::DataPlotter::addImuData(float data) noexcept(false){
    if(imuData_.size() > MAX_SIZE){
        throw DataPlotter::DataOverflow();
    }
    imuData_.push_back(data);
}

  apk::DataPlotter::imuBuffer* apk::DataPlotter::getImuData(){
    return &imuData_;
}