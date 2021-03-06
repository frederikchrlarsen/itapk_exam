//
// Created by frederik on 12/29/18.
//

#include <DataPlotter.h>

#include "DataPlotter.h"

void apk::DataPlotter::ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) {
    try {
        ultraSonicBuffer_.push_back(data);
    }catch (std::runtime_error &e){
        //std::cerr << "DataPlotter failed adding data to ultraSonicBuffer: "  << e.what() << std::endl;
    }
}

void apk::DataPlotter::imuSensorSignal(ImuSensor::ReturnType data) {

}

apk::DataPlotter::DataPlotter(double frameRate):
frameRate_(frameRate),
sleepTime_(calculateSleepTime(frameRate_)),
dataGenFuture_(dataGenPromise_.get_future())
{

}

apk::DataPlotter::DataPlotter():
frameRate_(DEFAULT_FPS),
sleepTime_(calculateSleepTime(frameRate_)),
dataGenFuture_(dataGenPromise_.get_future())
{

}

std::chrono::duration<double> apk::DataPlotter::calculateSleepTime(double frequency) const {
    return std::chrono::duration<double>(1/std::abs(frequency));
}

void apk::DataPlotter::loop() {
    while(loopRunning_){
        updateData();
        updateUltraDisplay();
        std::this_thread::sleep_for(sleepTime_);
    }

    dataGenPromise_.set_value(true);

}

void apk::DataPlotter::startLoop() {
    loopRunning_ = true;
    std::thread(&apk::DataPlotter::loop, this).detach();
}

void apk::DataPlotter::stopLoop() {
    if(loopRunning_){
        loopRunning_ = false;
        dataGenFuture_.wait();
    }
}

apk::DataPlotter::~DataPlotter() {
    stopLoop();
}

void apk::DataPlotter::updateData() {
    while(ultraSonicBuffer_.size() != 0){
        if(ultraSonicDataPosition_ == ultraSonicDataSize_)
            ultraSonicDataPosition_ = 0;
        try {
            ultraSonicData_[ultraSonicDataPosition_++] = ultraSonicBuffer_.pop().meters();
        }catch (std::runtime_error &e){
            std::cerr << "Error updating data: " << e.what() << std::endl;
        }
    }
}

void apk::DataPlotter::updateUltraDisplay() const {
    clearConsole();

    auto max = *std::max_element(ultraSonicData_.begin(), ultraSonicData_.end());
    std::array<long double, X_AXIS_LENGTH>data(ultraSonicData_);
    std::cout << "Max: " << max << std::endl;
    if(max > 0){
        //Divide each element in the array by max (Normalize)
        std::transform(data.begin(), data.end(), data.begin(),
                       [&](long double d) -> long double { return d/max; });
    }else{max = 1;}

    for(int i = 1; i <= y_; ++i){

        std::for_each(data.begin(), data.end(), [&](long double d){

            //if()

            if(i == y_)
                std::cout << "#";
            else
                std::cout << (d >= 1.0/i ? "#" :" ");

        });
        std::cout << std::endl;
    }
}

void apk::DataPlotter::clearConsole() const {
    //https://stackoverflow.com/questions/6486289/how-can-i-clear-console
    #if defined _WIN32
        system("CLS");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        //printf("\033[2J");
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}
