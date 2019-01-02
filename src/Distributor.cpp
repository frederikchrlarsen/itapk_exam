//
// Created by frederik on 12/27/18.
//

#include "Distributor.h"

void apk::Distributor::connectToSensor(apk::Subscriber *sub, sensorPtrType sensor) {
    if(this->isSensorInList(sensor)){

        //Generate the conMapKeyType from the Subscriber and the Sensor
        conMapKeyType key(sub, sensor);

        //Find the key in the map
        auto iterOfMap = subSensorConMap_.find(key);

        //If the key was in the map, the Subscriber is already connected to the Sensor.
        //No throw, since it is assumed the Subscriber just wants to keep the connection.
        if(iterOfMap != subSensorConMap_.end()){
            std::cerr << "Subscriber: " << sub << " already connected to the sensor: " << sensor << std::endl;
            return;
        }

        //Switch on the Sensor type, so the correct boost::function signature can be used for
        // the signal
        switch(sensor->getSensorType()){
            case apk::Sensor::ULTRASONIC:{

                //Bind the callback function (ultraSonicSensorSignal) to the Subscriber
                auto boostMethod = boost::bind(&apk::Subscriber::ultraSonicSensorSignal, sub, _1);

                //Insert the connection into the map
                subSensorConMap_.insert(std::make_pair(key, this->ultraSonicSensorSignal_.connect(boostMethod)));
                break;
            }
            case apk::Sensor::IMU:{
                auto boostMethod = boost::bind(&apk::Subscriber::imuSensorSignal, sub, _1);

                subSensorConMap_.insert(std::make_pair(key, this->imuSensorSignal_.connect(boostMethod)));

                break;
            }
            default:{
                //If the Sensor type is not implemented to work with the system, the function should throw.
                throw std::runtime_error("Error assigning signal to subscriber");
            }
        }
    }
}

void apk::Distributor::disconnectFromSensor(apk::Subscriber *sub, sensorPtrType sensor) {

    //Generate the conMapKeyType from the Subscriber and the Sensor
    conMapKeyType key(sub, sensor);

    //Find the key in the map
    auto iterOfMap = subSensorConMap_.find(key);

    //If the key was not in the map, the Subscriber was not connected to the sensor.
    if(iterOfMap == subSensorConMap_.end()){
        std::cerr << "Subscriber: " << sub << " already disconnected from the sensor: " << sensor << std::endl;
        return;
    }

    //Disconnet the boost::signals2::connection
    iterOfMap->second.disconnect();

    //Remove the key from the map
    subSensorConMap_.erase(key);
}

void apk::Distributor::addSensor(sensorPtrType sensor) {
    this->sensorList_.push_back(sensor);
}

void apk::Distributor::removeSensor(sensorPtrType sensor) {
    this->sensorList_.remove(sensor);
}

void apk::Distributor::connectSensor(sensorPtrType sensor) {

    //The connection can only be made if the Sensor is added
    if(this->isSensorInList(sensor)){

        //"Connect" the sensor, which should be under stood as physically connecting the Sensor
        sensor->connect();

        //Switch on the Sensor type to determine what signal should be used for connection
        switch(sensor->getSensorType()){
            case apk::Sensor::ULTRASONIC :{

                //Cast the Sensor pointer to the correct Sensor
                auto ultra = (UltraSonicSensor*) sensor;

                //Parse the signal, which the Sensor should call when new data is available
                ultra->connectSignal(ultraSonicSensorSignal_);
                break;
            }
            case apk::Sensor::IMU :{
                auto imu = (apk::ImuSensor*) sensor;

                imu->connectSignal(imuSensorSignal_);
            }
            default:{
                //TODO Error handling
                std::cerr << "Sensor type unknown" << std::endl;
            }
        }
    }else{
        //If the Sensor is not added to the Sensor list, simply add it and connect again.
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
    //Return true if the Sensor is found in the list, otherwise false
    return (std::find(this->sensorList_.begin(), this->sensorList_.end(), sensor) != this->sensorList_.end());
}

std::list<apk::Distributor::sensorPtrType> apk::Distributor::getSensorList() {
    //TODO Implement
    return std::list<apk::Distributor::sensorPtrType>();
}


