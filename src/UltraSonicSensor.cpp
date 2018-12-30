//
// Created by frederik on 12/30/18.
//


#include <sensors/UltraSonicSensor.h>

#include "sensors/UltraSonicSensor.h"

apk::UltraSonicSensor::UltraSonicSensor():
sensorType_(apk::Sensor::SensorType::ULTRASONIC),
signal_(nullptr)
{

}

apk::UltraSonicSensor::UltraSonicSensor(apk::UltraSonicSensor::SignalType &sigType):
sensorType_(apk::Sensor::SensorType::ULTRASONIC),
signal_(&sigType)
{
    threadDataGen_ = std::thread(&UltraSonicSensor::dataGenerator, this);
    threadDataGen_.detach();
}

apk::UltraSonicSensor::~UltraSonicSensor() {
    disconnect();
    running_ = false;
    dataGenFuture_.wait();
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

apk::Sensor::SensorType apk::UltraSonicSensor::getSensorType() const {
    return sensorType_;
}

void apk::UltraSonicSensor::connectSignal(apk::UltraSonicSensor::SignalType &sigType) {
    signal_ = &sigType;
}

void apk::UltraSonicSensor::setSampleRate(apk::UltraSonicSensor::SampleRate sampleRateArg) {
    sampleRate_ = sampleRateArg;
}

void apk::UltraSonicSensor::setDistanceType(apk::UltraSonicSensor::DistanceType distanceArg) {
    distanceType_ = distanceTypeTranslator(distanceArg);
}

void apk::UltraSonicSensor::dataGenerator() {
    while(running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)/sampleRate_);
        counter = counter + apk::Length{1, apk::Length::METER};

        if (isConnected()) {
            std::cout << "Calling signal " << "isConnected: " << isConnected() << " isRunning: " << running_ << std::endl;
            (*signal_)(counter);
        }
    }
    std::move(dataGenPromise_);
}

apk::Length::unit apk::UltraSonicSensor::distanceTypeTranslator(apk::UltraSonicSensor::DistanceType state) {
    if(state == METER){
        return apk::Length::METER;
    } else if (state == CM) {
        return apk::Length::CM;
    } else {
        std::cout << "Unknown setting." << std::endl;
    }
}


