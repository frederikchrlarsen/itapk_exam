//
// Created by frederik on 12/28/18.
//

#ifndef ITAPK_EXAM_ULTRASONICSENSOR_H
#define ITAPK_EXAM_ULTRASONICSENSOR_H


#include <Sensor.h>
#include <thread>
#include <list>
#include <boost/any.hpp>

template<class T>
class UltraSonicSensor: public apk::Sensor {

public:
    void addCallback(std::function<void(boost::any)> callback) override {
        dataCallback.push_back(callback);
    }

    void connect() override {
        std::thread thread_data_gen(&UltraSonicSensor::dataGenerator, this);
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

    bool isConnected(){
        //std:lock_guard<std::mutex> lock(mutex_connect);
        return connected;
    }

    void disconnect() override {
        //std:lock_guard<std::mutex> lock(mutex_connect);
        //disconnected = true;
        connected = false;
    }


private:
    bool connected = true;
    //std::mutex mutex_connect;
    int counter = 0;
    std::list<std::function<void(T)>> dataCallback;


};

#endif //ITAPK_EXAM_ULTRASONICSENSOR_H
