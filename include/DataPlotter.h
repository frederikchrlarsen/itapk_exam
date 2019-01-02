//
// Created by frederik on 12/29/18.
//

#ifndef ITAPK_EXAM_DATAPLOTTER_H
#define ITAPK_EXAM_DATAPLOTTER_H
#define MAX_SIZE 1024
#define DEFAULT_FPS 30

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
            return "Too many elements in the deque";
        }
    };

    // TODO Add Imu::returnType
    typedef std::deque<float> imuBuffer;

    DataPlotter();

    DataPlotter(double frameRate);
    ~DataPlotter();

    std::chrono::duration<double> calculateSleepTime(double frequency) const;

    void startLoop();

    void stopLoop();

    void clearConsole() const;

    void updateUltraDisplay() const;

    void imuSensorSignal(UltraSonicSensor::ReturnType data) override;

    void ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) override;

    imuBuffer* getImuData();
    friend std::ostream& operator<< ( std::ostream& o, apk::DataPlotter& plotter ) {
        std::deque<float>* que = plotter.getImuData();

        o << "############" << std::endl << "{";
        std::for_each(que->begin(), que->end(), [&](float &data){ o << data << ", ";});

        return o << "}" << std::endl << "############" << std::endl;
    }

    void addImuData (float data ) noexcept(false);
private:
    void loop();
    void updateData();

    double frameRate_;
    std::chrono::duration<double> sleepTime_;
    bool loopRunning_ = false;
    std::promise<bool> dataGenPromise_;
    std::future<bool> dataGenFuture_;

    apk::SensorData<apk::UltraSonicSensor::ReturnType, 10> ultraSonicBuffer_;
    std::array<long double, 50> ultraSonicData_ = {0};
    unsigned int ultraSonicDataSize_ = 50;
    unsigned int ultraSonicDataPosition_ = 0;
    unsigned int x_, y_ = 30;

    size_t imuBufferSize_;
    imuBuffer imuData_;
};



}

#endif //ITAPK_EXAM_DATAPLOTTER_H
