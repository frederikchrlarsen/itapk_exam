#include <iostream>
#include <functional>
#include <chrono>
#include <Subscriber.h>
#include <Distributor.h>
#include <DataPlotter.h>
#include "Imu.h"
#include "Sensor.h"
#include "UltraSonicSensor.h"
#include <manipulateData.h>


void testDist();

void testLength();

void testUltraSonicSensor();

int main() {
    //testLength();
    //testUltraSonicSensor();
    testDist();

    /*

    apk::DataPlotter sub1, sub2;

    manipulateData m1;
    m1.addSubscriber(&sub1);
    m1.addSubscriber(&sub2);
    m1.forEach();
    m1.accumulate();

    int accumulatedId = m1();
    std::cout << std::endl;
    std::cout << accumulatedId;

     */
    return 0;
}

void testDist(){

    apk::Distributor dist;

    apk::DataPlotter sub1, sub2;
    dist.addSubscriber(&sub1);
    dist.addSubscriber(&sub2);
    dist.test();

    // Callback function as a lambda expression for now
    //std::function<void(float)> call = [&](float a){ std::cout << a << std::endl; };

    // The sensor interface
    apk::Sensor* imu;
    // Instantiate an Imu sensor
    imu = new apk::Imu<float>;

    apk::Sensor* ultraSonicSensor;
    ultraSonicSensor = new apk::UltraSonicSensor;
    auto ultraSonicSensorPtr = (apk::UltraSonicSensor*) ultraSonicSensor;

    dist.addSensor(ultraSonicSensor);
    dist.connectSensor(ultraSonicSensor);
    dist.subConnectToSensor(&sub1, ultraSonicSensor);


    dist.addSensor(imu);
    dist.connectSensor(imu);
    dist.subConnectToSensor(&sub1, imu);
    // Connect to the sensor
    //imu->connect();

    // Let the Imu thread run and disconnect after
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.subConnectToSensor(&sub2, imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.removeSubscriber(&sub2);
    ultraSonicSensorPtr->setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.disconnectSensor(imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    //imu->disconnect();

    std::cout << imu->test() << std::endl;
}

void testLength() {
    using namespace apk::literals;

    auto x1 = 10.0_km;
    auto x2 = 20.0_mi;
    auto x3 = 15.0_cm;
    auto x4 = 10_m;
    auto x5 = 10_m - 15_m;

    auto total = x1 + x2 + x3 + x4 - 115.0_m;

    std::cout << "Km:" << x1.kilometers() << std::endl;
    std::cout << "Mi:" << x1.miles() << std::endl << std::endl;

    std::cout << "MILES: " << x2.miles() << std::endl;
    std::cout << "Km: " << x2.kilometers() << std::endl << std::endl;

    std::cout << "Total miles: " << total.miles() << std::endl;
    std::cout << "Total km: " << total.kilometers() << std::endl;
    std::cout << "x4 m: " << x4.meters() << std::endl;
}

void testUltraSonicSensor(){

    using namespace std::literals;
    typedef apk::UltraSonicSensor::ReturnType UltraSonicSensorDataType;
    typedef apk::UltraSonicSensor::SignalType UltraSonicSensorSignal;

    struct printLength{
        void operator()(UltraSonicSensorDataType length){
            std::cout << "Length in meters: " << length.meters() << std::endl;
        }
    };

    UltraSonicSensorSignal sig;

    apk::UltraSonicSensor ultraSonicSensor(sig);

    sig.connect(printLength());

    ultraSonicSensor.connect();
    std::this_thread::sleep_for(5000ms);

    ultraSonicSensor.disconnect();
    ultraSonicSensor.setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(1000ms);

    ultraSonicSensor.connect();
    std::this_thread::sleep_for(5000ms);
    ultraSonicSensor.disconnect();
    std::this_thread::sleep_for(1000ms);
}