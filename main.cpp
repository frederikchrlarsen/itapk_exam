#include <iostream>
#include <functional>
#include <chrono>
#include <Subscriber.h>
#include "Imu.h"
#include "Sensor.h"
#include "units.h"

int main() {
    //using namespace std::literals;

    //std::cout << "Number to degrees: " << 2.0_deg << std::endl;
    //auto x = 2.0h;
    //auto y = 2.0min;
    //auto res = x-y;

    //std::cout << "Test: " << res.count() << std::endl;
    testLength();
    //"asd"_print;

//    apk::Subscriber sub;
//    sub.test();
//
//    // Callback function as a lambda expression for now
//    std::function<void(std::string)> call = [&](std::string a){ std::cout << a << std::endl; };
//
//    // The sensor interface
//    apk::Sensor<float>* imu;
//
//    // Instantiate an Imu sensor
//    imu = new apk::Imu<float>(call);
//
//    // Connect to the sensor
//    imu->connect();
//
//    // Let the Imu thread run and disconnect after
//    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
//    imu->disconnect();
//
//    std::cout << imu->test() << std::endl;
    return 0;
}