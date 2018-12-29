//
// Created by frederik on 12/29/18.
//

#ifndef ITAPK_EXAM_SENSORINFO_H
#define ITAPK_EXAM_SENSORINFO_H

#include <string>

namespace apk {

class SensorInfo {

public:
    enum SensorType {
        Imu = 1,
        DistanceSensor = 2,
        Encoder = 3
    };

    SensorInfo(std::string model, const apk::SensorInfo::SensorType sensorType):
    model_(std::move(model)),
    sensorType_(sensorType)
    {

    }

    std::string model_;
    apk::SensorInfo::SensorType sensorType_;
};
}

#endif //ITAPK_EXAM_SENSORINFO_H
