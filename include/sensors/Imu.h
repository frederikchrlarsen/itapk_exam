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

template <class T>
class Imu: public apk::Sensor<T> {

public:
    explicit Imu(std::function<void(std::string)> callback){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        data_callback = callback;
    }

    std::string test(){
        return "Imu test";
    }

    void connect() {

        std::thread thread_data_gen(&Imu::data_generator, this);
        thread_data_gen.detach();
    }

    void data_generator(){
        while(is_connected()){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            data_callback(std::to_string(counter++));
        }
    }

    bool is_connected(){
        //std:lock_guard<std::mutex> lock(mutex_connect);
        return !disconnected;
    }

    void disconnect() {
        //std:lock_guard<std::mutex> lock(mutex_connect);
        //disconnected = true;
        disconnected = true;
    }

private:
    bool disconnected = false;
    //std::mutex mutex_connect;
    int counter = 0;
    std::function<void(std::string)> data_callback;

};

}
#endif //ITAPK_EXAM_IMU_H
