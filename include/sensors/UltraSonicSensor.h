//
// Created by frederik on 12/28/18.
//

#ifndef ITAPK_EXAM_ULTRASONICSENSOR_H
#define ITAPK_EXAM_ULTRASONICSENSOR_H


#include <Sensor.h>
#include <thread>
#include <list>
#include <units.h>
#include <chrono>
#include <iostream>
#include <ctime>

using namespace std::literals;

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
    typedef Length ReturnType;
    typedef boost::signals2::signal<void (Length)> SignalType;

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

    UltraSonicSensor():
    sensorType_(apk::Sensor::SensorType::ULTRASONIC)
    {

    };

    explicit UltraSonicSensor(SignalType& sigType):
    sensorType_(apk::Sensor::SensorType::ULTRASONIC)
    {
        signal_ = &sigType;
        std::thread thread_data_gen(&UltraSonicSensor::dataGenerator, this);
        thread_data_gen.detach();
    }

    ~UltraSonicSensor(){
        running = false;
    }

    apk::Sensor::SensorType getSensorType() const {
        return sensorType_;
    }

    void connectSignal(SignalType& sigType){
        signal_ = &sigType;
    }

    void setSampleRate(UltraSonicSensor::SampleRate sampleRateArg){
        sampleRate = sampleRateArg;
    }

    void setDistanceType(UltraSonicSensor::DistanceType distanceArg){
        distanceType = distanceTypeTranslator(distanceArg);
    }

private:
    apk::Sensor::SensorType sensorType_;
    bool running = true;
    float sampleRate = 1;
    Length::unit distanceType = distanceTypeTranslator(METER);
    Length counter = Length{0, distanceType};
    SignalType* signal_;

    void dataGenerator(){
        while(running) {
            std::this_thread::sleep_for(1000ms/sampleRate);
            counter = counter + Length{1, Length::METER};

            if (isConnected()) {
                (*signal_)(counter);
            }
        }
    }

    Length::unit distanceTypeTranslator(DistanceType state){
        if(state == METER){
            return Length::METER;
        } else if (state == CM) {
            return Length::CM;
        } else {
            std::cout << "Unknown setting." << std::endl;
        }
    }
};

/*
void testUltraSonicSensor(){
    typedef UltraSonicSensor::ReturnType UltraSonicSensorDataType;
    typedef UltraSonicSensor::SignalType UltraSonicSensorSignal;

    struct printLength{
        void operator()(UltraSonicSensorDataType length){
                std::cout << "Length in meters: " << length.meters() << std::endl;
            }
    };

    UltraSonicSensorSignal sig;

    UltraSonicSensor ultraSonicSensor(sig);

    sig.connect(printLength());

    ultraSonicSensor.connect();
    std::this_thread::sleep_for(5000ms);

    ultraSonicSensor.disconnect();
    ultraSonicSensor.setSampleRate(UltraSonicSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(1000ms);

    ultraSonicSensor.connect();
    std::this_thread::sleep_for(5000ms);
    ultraSonicSensor.disconnect();
    std::this_thread::sleep_for(1000ms);
}*/


#endif //ITAPK_EXAM_ULTRASONICSENSOR_H
