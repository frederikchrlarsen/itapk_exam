//
// Created by frederik on 12/28/18.
//

#ifndef ITAPK_EXAM_ULTRASONICSENSOR_H
#define ITAPK_EXAM_ULTRASONICSENSOR_H


#include "Sensor.h"
#include <thread>
#include <list>
#include "Units.h"
#include <chrono>
#include <iostream>
#include <ctime>
#include <future>

using namespace apk::literals;

namespace apk{

    enum BitField{
        start = 0,
        data0 = 1,
        data1 = 2,
        sampleRate0 = 3,
        sampleRate1 = 4,
        sampleRate2 = 5,
        resolution0 = 6,
        resolution1 = 7
    };

    class UltraSonicSensor: public apk::Sensor {

    public:
        typedef apk::Length ReturnType;
        typedef boost::signals2::signal<void (apk::Length)> SignalType;
        typedef std::chrono::time_point<std::chrono::high_resolution_clock> timePointType;

        enum SampleRate{
            HZ_1 = 1,
            HZ_2 = 2,
            HZ_5 = 5,
            HZ_10 = 10
        };

        enum DistanceType{
            CM,
            METER
        };

        UltraSonicSensor();

        explicit UltraSonicSensor(SignalType& sigType);

        ~UltraSonicSensor();

        apk::Sensor::SensorType getSensorType() const override;

        void connectSignal(SignalType& sigType);

        void setSampleRate(UltraSonicSensor::SampleRate sampleRateArg);

        void setDistanceType(UltraSonicSensor::DistanceType distanceArg);

    private:
        void dataGenerator();

        ReturnType generateSine(timePointType & startTime);

        apk::Length::unit distanceTypeTranslator(DistanceType state);

        //Threading
        std::promise<bool> dataGenPromise_;
        std::future<bool> dataGenFuture_ = dataGenPromise_.get_future();
        bool running_ = false;

        float sampleRate_ = 1;
        apk::Sensor::SensorType sensorType_;
        apk::Length::unit distanceType_ = distanceTypeTranslator(METER);

        SignalType* signal_;
    };


}

#endif //ITAPK_EXAM_ULTRASONICSENSOR_H
