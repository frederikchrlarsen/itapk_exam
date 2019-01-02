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
//#include "UltraSonicSensor.h

namespace apk {
    class Regulator : public Subscriber {
    public:
        Regulator();

        void imuSensorSignal(apk::ImuSensor::ReturnType data) override;

        void ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) override;

        void run(){
            running_ = true;
            std::thread(&apk::Regulator::controlLoop, this).detach();
        }
    private:
        void controlLoop();

        Length ultraSonicData=10_m;
        ImuSensor::ReturnType imuData = 12.2;
        bool running_ = false;
    };
}
/*void testRegulator(){
    Regulator regulator;
    regulator.run();
}*/


#endif //ITAPK_EXAM_REGULATOR_H
