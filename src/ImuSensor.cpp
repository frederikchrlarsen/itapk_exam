//
// Created by frederik on 1/2/19.
//

#include "ImuSensor.h"

apk::ImuSensor::ImuSensor():
        sensorType_(apk::Sensor::SensorType::IMU),
        signal_(nullptr),
        running_(true)
{
    std::thread(&apk::ImuSensor::dataGenerator, this).detach();
}

apk::ImuSensor::ImuSensor(apk::ImuSensor::SignalType &sigType):
        sensorType_(apk::Sensor::SensorType::IMU),
        signal_(&sigType),
        running_(true)
{
    std::thread(&apk::ImuSensor::dataGenerator, this).detach();
}

apk::ImuSensor::~ImuSensor(){
    disconnect();
    running_ = false;
    dataGenFuture_.wait();
};

apk::Sensor::SensorType apk::ImuSensor::getSensorType() const {
    return sensorType_;
}

void apk::ImuSensor::connectSignal(apk::ImuSensor::SignalType &sigType) {
    signal_ = &sigType;
}

void apk::ImuSensor::setSampleRate(apk::ImuSensor::SampleRate sampleRateArg) {
    sampleRate_ = sampleRateArg;
}

void apk::ImuSensor::dataGenerator() {
    auto startTime = std::chrono::high_resolution_clock::now();

    while(running_) {

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)/sampleRate_);

        if (isConnected() && signal_ != nullptr) {
            (*signal_)(generateRand());
        }
    }
    dataGenPromise_.set_value(true);
}

apk::ImuSensor::ReturnType apk::ImuSensor::generateRand() {

    return static_cast<ReturnType>(std::rand());
}
