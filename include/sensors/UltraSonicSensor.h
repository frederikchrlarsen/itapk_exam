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
        //Threading
        std::promise<bool> dataGenPromise_;
        std::future<bool> dataGenFuture_ = dataGenPromise_.get_future();

        std::thread threadDataGen_;
        apk::Sensor::SensorType sensorType_;
        bool running_ = true;
        float sampleRate_ = 1;
        apk::Length::unit distanceType_ = distanceTypeTranslator(METER);
        apk::Length counter = apk::Length{0, distanceType_};
        SignalType* signal_;

        void dataGenerator();

        apk::Length::unit distanceTypeTranslator(DistanceType state);
    };


}

#endif //ITAPK_EXAM_ULTRASONICSENSOR_H
