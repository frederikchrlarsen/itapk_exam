//
// Created by frederik on 12/30/18.
//

#include <cmath>
#include "sensors/UltraSonicSensor.h"

apk::UltraSonicSensor::UltraSonicSensor():
sensorType_(apk::Sensor::SensorType::ULTRASONIC),
signal_(nullptr),
running_(true)
{
    std::thread(&UltraSonicSensor::dataGenerator, this).detach();
}

apk::UltraSonicSensor::UltraSonicSensor(apk::UltraSonicSensor::SignalType &sigType):
sensorType_(apk::Sensor::SensorType::ULTRASONIC),
signal_(&sigType),
running_(true)
{
    std::thread(&UltraSonicSensor::dataGenerator, this).detach();
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
    auto startTime = std::chrono::high_resolution_clock::now();

    while(running_) {

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)/sampleRate_);

        if (isConnected() && signal_ != nullptr) {
            (*signal_)(generateSine(startTime));
        }
    }
    dataGenPromise_.set_value(true);
}

apk::Length::unit apk::UltraSonicSensor::distanceTypeTranslator(apk::UltraSonicSensor::DistanceType state) {
    if(state == METER){
        return apk::Length::METER;
    } else if (state == CM) {
        return apk::Length::CM;
    } else {
        std::cout << "Unknown setting." << std::endl;
        throw "unknown setting";
    }
}

apk::UltraSonicSensor::ReturnType apk::UltraSonicSensor::generateSine(timePointType &startTime) {

    auto timeTemp = std::chrono::high_resolution_clock::now() - startTime;
    auto timeElapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(timeTemp);
    double t = timeElapsedMs.count()/1000.0;
    double fs = 0.3;

    ReturnType length(std::sin(t*2*M_PI*fs)+1, distanceType_);
    return length;
}


