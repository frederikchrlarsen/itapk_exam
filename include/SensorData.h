//
// Created by frederik on 12/27/18.
//

#ifndef ITAPK_EXAM_SENSORDATA_H
#define ITAPK_EXAM_SENSORDATA_H

#include <algorithm>

#define MAX_MEMORY 2048


namespace apk{
    template<class T, std::size_t size>
    class SensorData {

    public:

        SensorData();

        explicit SensorData(T data[]);

        ~SensorData();

        void resize(std::size_t newSize) noexcept(false);

        SensorData& operator=(SensorData&& other) noexcept;

    private:
        std::size_t size_;
        T* data_;
    };

    template<class T, size_t size>
    SensorData<T, size>::SensorData():
    size_(size),
    data_(new T[size])
    {

    }

    template<class T, size_t size>
    SensorData<T, size>::SensorData(T *data):
    size_(size)
    {
        data_ = new T[size_];
        std::copy(data, data+sizeof(T)*size, data_);
    }

    template<class T, size_t size>
    SensorData<T, size>::~SensorData() {
        delete data_;
    }

    template<class T, size_t size>
    void SensorData<T, size>::resize(std::size_t newSize) noexcept(false) {

    }

    template<class T, size_t size>
    SensorData<T, size> &SensorData<T, size>::operator=(SensorData &&other) noexcept {
        return *this;
    }


}




#endif //ITAPK_EXAM_SENSORDATA_H
