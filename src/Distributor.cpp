//
// Created by frederik on 12/27/18.
//

#include "Distributor.h"

void apk::Distributor::connectToSensor(apk::Subscriber *sub, sensorPtrType sensor) {
    if(this->isSensorInList(sensor)){

        conMapKeyType key(sub, sensor);
        auto iterOfMap = subSensorConMap_.find(key);
        if(iterOfMap != subSensorConMap_.end()){
            //TODO Error handling
            std::cerr << "Subscriber: " << sub << " already connected to the sensor: " << sensor << std::endl;
            return;
        }

        switch(sensor->getSensorType()){
            case apk::Sensor::ULTRASONIC:{
                std::cout << "Connecting subscriber to signal" << std::endl;
                auto boostMethod = boost::bind(&apk::Subscriber::ultraSonicSensorSignal, sub, _1);
                subSensorConMap_.insert(std::make_pair(key, this->ultraSonicSensorSignal_.connect(boostMethod)));
                break;
            }
            case apk::Sensor::IMU:{
                break;
            }
            default:{
                //TODO Error handling
                throw "Error assigning signal to subscriber";
            }
        }
    }
}

void apk::Distributor::disconnectFromSensor(apk::Subscriber *sub, sensorPtrType sensor) {
    conMapKeyType key(sub, sensor);
    auto iterOfMap = subSensorConMap_.find(key);
    if(iterOfMap == subSensorConMap_.end()){
        //TODO Error handling
        std::cerr << "Subscriber: " << sub << " already disconnected from the sensor: " << sensor << std::endl;
        return;
    }
    iterOfMap->second.disconnect();
    subSensorConMap_.erase(key);
}

void apk::Distributor::addSensor(sensorPtrType sensor) {
    this->sensor_.push_back(sensor);
}

void apk::Distributor::removeSensor(sensorPtrType sensor) {
    this->sensor_.remove(sensor);
}

void apk::Distributor::connectSensor(sensorPtrType sensor) {
    if(this->isSensorInList(sensor)){
        sensor->connect();
        switch(sensor->getSensorType()){
            case apk::Sensor::ULTRASONIC :{
                auto ultra = (UltraSonicSensor*) sensor;
                ultra->connectSignal(ultraSonicSensorSignal_);
                std::cout << "Adding signal to Ultra Sensor" << std::endl;
                break;
            }
            case apk::Sensor::IMU :{

            }
            default:{
                //TODO Error handling
                std::cerr << "Sensor type unknown" << std::endl;
            }
        }
    }else{
        this->addSensor(sensor);
        this->connectSensor(sensor);
    }
}

void apk::Distributor::disconnectSensor(sensorPtrType sensor) {
    if(this->isSensorInList(sensor)){
        sensor->disconnect();
    }
}

bool apk::Distributor::isSensorInList(sensorPtrType sensor) {
    // InputIt find( InputIt first, InputIt last, const T& value );
    return (std::find(this->sensor_.begin(), this->sensor_.end(), sensor) != this->sensor_.end());
}

std::list<apk::Distributor::sensorPtrType> apk::Distributor::getSensorList() {
    //TODO Implement
    return std::list<apk::Distributor::sensorPtrType>();
}


