//
// Created by Taise on 29/12/2018.
//

#ifndef ITAPK_EXAM_REGULATOR_H
#define ITAPK_EXAM_REGULATOR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <sensors/Imu.h>
#include "Subscriber.h"
#include <boost/thread.hpp>


// REF: Inspiration for timer from https://www.boost.org/doc/libs/1_69_0/doc/html/boost_asio/tutorial/tuttimer3/src.html

namespace apk {

    class Regulator : public Subscriber {
    public:
        Regulator(int regulateRateHZ);
        ~Regulator();

        void imuSensorSignal(Imu::ReturnType data) override;

        void ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) override;

        void run(){
            running_ = true;
            std::thread(&controlLoop, this).detach();
        }

    private:
        void controlLoop();
        void doAdvancedRegulationAlgorithms();
        Length ultraSonicData = 10_m;
        Imu::ReturnType imuData = 12.2;
        int regulateRateHZ_;
        bool running_ = false;
        boost::mutex threadMut_;

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
