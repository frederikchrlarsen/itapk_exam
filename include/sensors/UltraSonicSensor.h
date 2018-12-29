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
#include <c++/8.1.0/iostream>
#include <ctime>

using namespace std::literals;

class UltraSonicSensor: public apk::Sensor {

public:
    typedef Length ReturnType;
    typedef boost::signals2::signal<void (Length)> SignalType;

    void addCallback(std::function<void(boost::any)> callback) override {
        dataCallback.push_back(callback);
    }

    void connect()override{};

    void connectSignal(SignalType& sigType) {
        signal_ = &sigType;
        std::thread thread_data_gen(&UltraSonicSensor::dataGenerator, this);
        thread_data_gen.detach();
        connected = true;
    }

    void dataGenerator(){
        while(isConnected()){
            std::this_thread::sleep_for(500ms);
            (*signal_)(counter);
            counter = counter + Length{1, Length::METER};
        }
    }

private:
    Length counter = Length{0, Length::METER};
    SignalType* signal_;
    std::list<std::function<void(Length)>> dataCallback;
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

    UltraSonicSensor ultraSonicSensor;

    sig.connect(printLength());

    ultraSonicSensor.connectSignal(sig);

    _sleep(5000);
}

#endif //ITAPK_EXAM_ULTRASONICSENSOR_H
