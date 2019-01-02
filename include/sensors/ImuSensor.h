//
// Created by Frederik on 16-12-2018.
//

#include <iostream>
#include <future>
#include "Sensor.h"
//#include "mutex"
#include "thread"
#include "chrono"

#ifndef ITAPK_EXAM_IMU_H
#define ITAPK_EXAM_IMU_H

namespace apk{

class ImuSensor: public apk::Sensor {

public:
    typedef double ReturnType;
    typedef boost::signals2::signal<void (ReturnType)> SignalType;

    enum SampleRate{
        HZ_1 = 1,
        HZ_2 = 2,
        HZ_5 = 5,
        HZ_10 = 10
    };

    ImuSensor();

    explicit ImuSensor(SignalType& sigType);

    ~ImuSensor();

    apk::Sensor::SensorType getSensorType() const override;

    void connectSignal(SignalType& sigType);

    void setSampleRate(ImuSensor::SampleRate sampleRateArg);

private:
    void dataGenerator();

    ReturnType generateRand();

    std::promise<bool> dataGenPromise_;
    std::future<bool> dataGenFuture_ = dataGenPromise_.get_future();
    bool running_ = false;

    float sampleRate_ = 1;
    apk::Sensor::SensorType sensorType_;

    SignalType* signal_;

};

}
#endif //ITAPK_EXAM_IMU_H
