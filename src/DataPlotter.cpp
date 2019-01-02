//
// Created by frederik on 12/29/18.
//

#include <DataPlotter.h>

#include "DataPlotter.h"


void apk::DataPlotter::addImuData(float data) noexcept(false){
    if(imuData_.size() > MAX_SIZE){
        throw DataPlotter::DataOverflow();
    }
    imuData_.push_back(data);
}

  apk::DataPlotter::imuBuffer* apk::DataPlotter::getImuData(){
    return &imuData_;
}

void apk::DataPlotter::ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) {
    try {
        ultraSonicBuffer_.push_back(data);
        std::cout << "Got data: " << data << std::endl;
    }catch (std::runtime_error &e){
        std::cerr << "DataPlotter failed adding data to ultraSonicBuffer: "  << e.what() << std::endl;
    }
}

void apk::DataPlotter::imuSensorSignal(UltraSonicSensor::ReturnType data) {

}

apk::DataPlotter::DataPlotter(unsigned int frameRate):
frameRate_(frameRate),
sleepTime_(calculateSleepTime(frameRate_))
{

}

apk::DataPlotter::DataPlotter():
frameRate_(DEFAULT_FPS),
sleepTime_(calculateSleepTime(frameRate_))
{

}

std::chrono::seconds apk::DataPlotter::calculateSleepTime(unsigned int frequency) const {
    return std::chrono::seconds(1/frequency);
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
    dataGenFuture_ = dataGenPromise_.get_future();
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
    std::array<long double, 20>data(ultraSonicData_);
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
                std::cout << "•";
            else
                std::cout << (d >= 1.0/i ? "•" :" ");

        });
        std::cout << std::endl;
    }


    /*
    std::copy(ultraSonicData_.begin(), ultraSonicData_.end(),
            std::ostream_iterator<long double>(std::cout, " "));
    std::cout << std::endl;
     */
}

void apk::DataPlotter::clearConsole() const {
    //https://stackoverflow.com/questions/6486289/how-can-i-clear-console
    #if defined _WIN32
        printf("%s%s", "\33[", "31m");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        //printf("\033[2J");
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}
