//
// Created by Frederik on 16-12-2018.
//

#include <iostream>
#include "Sensor.h"
//#include "mutex"
#include "thread"
#include "chrono"

#ifndef ITAPK_EXAM_IMU_H
#define ITAPK_EXAM_IMU_H

namespace apk{

class Imu: public apk::Sensor {

public:
    typedef float ReturnType;

    Imu():sensorType_(apk::Sensor::SensorType::IMU){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    explicit Imu(std::function<void(ReturnType)> callback){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        dataCallback.push_back(callback);
    }

    std::string test() override {
        return "Imu test";
    }

    apk::Sensor::SensorType getSensorType() const{
        return sensorType_;
    }

    void addCallback(std::function<void(boost::any)> callback) override {
        dataCallback.push_back(callback);
    }

    void connect() override {
        std::thread thread_data_gen(&Imu::dataGenerator, this);
        thread_data_gen.detach();
    }

    void dataGenerator(){
        while(isConnected()){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            for(auto const& callback: dataCallback)
                callback(counter);
            counter++;
        }
    }

private:
    apk::Sensor::SensorType sensorType_;
    bool connected = true;
    //std::mutex mutex_connect;
    ReturnType counter = 0;
    std::list<std::function<void(ReturnType)>> dataCallback;

};

}
#endif //ITAPK_EXAM_IMU_H
