//
// Created by frederik on 12/27/18.
//

#include "Distributor.h"


void apk::Distributor::addSubscriber(apk::Subscriber *newSub) {
    std::cout << "Adding subscriber: " << newSub << std::endl;
    this->subscriber.push_back(newSub);
}

void apk::Distributor::removeSubscriber(apk::Subscriber *removingSub) {
    std::cout << "Removing subscriber: " << removingSub << std::endl;
    this->subscriber.remove(removingSub);
}

void apk::Distributor::subConnectToSensor(apk::Subscriber *sub, sensor_ptr sensor) {
    if(this->isSensorInList(sensor)){
        auto l = [&](int data){sub->dataCallback(data);};
        auto boundMethod = std::bind(&apk::Subscriber::dataCallback, sub, _1);
        boost::signals2::connection connection = this->sig.connect(l);
    }
}


void apk::Distributor::test() {
    for(auto const& i: this->subscriber){
        i->test();
    }
}

void apk::Distributor::addSensor(sensor_ptr sensor) {
    this->sensor.push_back(sensor);
}

void apk::Distributor::removeSensor(sensor_ptr sensor) {
    this->sensor.remove(sensor);
}

void apk::Distributor::connectSensor(sensor_ptr sensor) {
    if(this->isSensorInList(sensor)){
        sensor->connect();
        registerSensorCallback(sensor, [&](boost::any data){this->sensorCallback(boost::any_cast<float>(data));});
    }else{
        this->addSensor(sensor);
        this->connectSensor(sensor);
    }
}

void apk::Distributor::disconnectSensor(sensor_ptr sensor) {
    if(this->isSensorInList(sensor)){
        sensor->disconnect();
    }
}

void apk::Distributor::sensorCallback(float data) {
    this->sig(data);
}

bool apk::Distributor::isSensorInList(sensor_ptr sensor) {
    // InputIt find( InputIt first, InputIt last, const T& value );
    return (std::find(this->sensor.begin(), this->sensor.end(), sensor) != this->sensor.end());
}

void
apk::Distributor::registerSensorCallback(apk::Distributor::sensor_ptr sensor, const float_func &callback) {

    if(isSensorInList(sensor)){
        sensor->addCallback(callback);
    }

}


