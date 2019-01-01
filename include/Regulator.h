//
// Created by Taise on 29/12/2018.
//

#ifndef ITAPK_EXAM_REGULATOR_H
#define ITAPK_EXAM_REGULATOR_H

#include <iostream>
#include <chrono>
#include <thread>

class Regulator {
public:
    Regulator()=default;

    void run(){
        auto start = std::chrono::high_resolution_clock::now();
        controlLoop();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;

        std::cout << "Time elapsed: " << diff.count() << "s" << std::endl;
    }
private:
    void controlLoop(){
        //std::this_thread::sleep_for(50ms);
    }
    Length ultraSonicData;
    Float imuData;
};

void testRegulator(){
    Regulator regulator;
    regulator.run();
}


#endif //ITAPK_EXAM_REGULATOR_H
