//
// Created by frederik on 12/29/18.
//

#ifndef ITAPK_EXAM_DATAPLOTTER_H
#define ITAPK_EXAM_DATAPLOTTER_H
#define MAX_SIZE 1024

#include <deque>
#include "Subscriber.h"

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
    size_t imuBufferSize_;
    imuBuffer imuData_;
};

}

#endif //ITAPK_EXAM_DATAPLOTTER_H
