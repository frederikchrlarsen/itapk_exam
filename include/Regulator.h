//
// Created by Taise on 29/12/2018.
//

#ifndef ITAPK_EXAM_REGULATOR_H
#define ITAPK_EXAM_REGULATOR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <sensors/ImuSensor.h>
#include "Subscriber.h"


// REF: Inspiration for timer from https://www.boost.org/doc/libs/1_69_0/doc/html/boost_asio/tutorial/tuttimer3/src.html

namespace apk {

    class Regulator : public Subscriber {
    public:
        Regulator(int regulateRateHZ);
        ~Regulator();

        void imuSensorSignal(apk::ImuSensor::ReturnType data) override;

        void ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) override;

        void run();

        void stop();

    private:
        void controlLoop();

        ImuSensor::ReturnType imuData = 12.2;
        void doAdvancedRegulationAlgorithms();
        UltraSonicSensor::ReturnType ultraSonicData = 10_m;
        int regulateRateHZ_;
        bool running_ = false;
        std::mutex threadMut_;
    };

    struct RegulatorFailure : std::exception{
        const char * what () const noexcept override {
            return "Regulator loop too slow! Descrease algorithm evaluation time or decrease regulation HZ.";
        }
    };
}
/*void testRegulator(){
    Regulator regulator;
    regulator.run();
}*/


#endif //ITAPK_EXAM_REGULATOR_H
