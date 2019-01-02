//
// Created by frederik on 12/29/18.
//

#ifndef ITAPK_EXAM_DATAPLOTTER_H
#define ITAPK_EXAM_DATAPLOTTER_H
#define MAX_SIZE 1024
#define DEFAULT_FPS 30
#define X_AXIS_LENGTH 100

#include <deque>
#include "Subscriber.h"
#include "SensorData.h"
#include <stdio.h>

namespace apk{

class DataPlotter: public Subscriber {

public:

    struct DataOverflow : public std::exception
    {
        const char * what () const noexcept override {
            return "Too many elements";
        }
    };

    DataPlotter();

    explicit DataPlotter(double frameRate);

    ~DataPlotter();


    void startLoop();

    void stopLoop();

    void imuSensorSignal(ImuSensor::ReturnType data) override;

    void ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) override;

private:

    std::chrono::duration<double> calculateSleepTime(double frequency) const;

    void clearConsole() const;

    void updateUltraDisplay() const;

    void loop();

    void updateData();

    double frameRate_;
    std::chrono::duration<double> sleepTime_;

    bool loopRunning_ = false;
    std::promise<bool> dataGenPromise_;
    std::future<bool> dataGenFuture_;

    apk::SensorData<apk::UltraSonicSensor::ReturnType, 10> ultraSonicBuffer_;
    std::array<long double, X_AXIS_LENGTH> ultraSonicData_ = {0};
    unsigned int ultraSonicDataSize_ = X_AXIS_LENGTH;
    unsigned int ultraSonicDataPosition_ = 0;
    unsigned int x_ = 30, y_ = 30;

};

}

#endif //ITAPK_EXAM_DATAPLOTTER_H
