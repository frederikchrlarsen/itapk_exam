//
// Created by frederik on 12/28/18.
//

#ifndef ITAPK_EXAM_ULTRASONICSENSOR_H
#define ITAPK_EXAM_ULTRASONICSENSOR_H


#include <Sensor.h>
#include <thread>
#include <list>
#include <boost/any.hpp>
#include <units.h>
#include <chrono>
#include <iostream>
#include <ctime>

using namespace std::literals;

class UltraSonicSensor: public apk::Sensor {

public:
    typedef Length ReturnType;
    typedef boost::signals2::signal<void (Length)> SignalType;

    explicit UltraSonicSensor(SignalType& sigType) {
        signal_ = &sigType;
        std::thread thread_data_gen(&UltraSonicSensor::dataGenerator, this);
        thread_data_gen.detach();
    }

    ~UltraSonicSensor(){
        running = false;
    }

    void dataGenerator(){
        while(running) {
            std::this_thread::sleep_for(500ms);
            counter = counter + Length{1, Length::METER};

            if (isConnected()) {
                (*signal_)(counter);
            }
        }
    }

private:
    bool running = true;
    Length counter = Length{0, Length::METER};
    SignalType* signal_;
};


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
    std::this_thread::sleep_for(1000ms);

    ultraSonicSensor.connect();
    std::this_thread::sleep_for(5000ms);
    ultraSonicSensor.disconnect();
    std::this_thread::sleep_for(1000ms);
}

#endif //ITAPK_EXAM_ULTRASONICSENSOR_H
