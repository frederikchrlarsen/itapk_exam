//
// Created by frederik on 12/27/18.
//

#ifndef ITAPK_EXAM_SENSORDATA_H
#define ITAPK_EXAM_SENSORDATA_H

#include <algorithm>
#include <ostream>

#define MAX_MEMORY 2048


namespace apk{
    template<class T, std::size_t sizeT>
    class SensorData {

    public:

        SensorData();

        explicit SensorData(T data[]);

        ~SensorData();

        void resize(std::size_t newSize) noexcept(false);

        size_t getSize();

        T* begin();

        T* begin()const;

        T* end();

        T* end()const;

        void push_back(T &&data);
        
        size_t size();

        T pop();

        SensorData& operator=(SensorData&& other) noexcept;

        T& operator [](int i) {
            return data_[i];
        }

        template<T, size_t>
        friend std::ostream& operator<< ( std::ostream& o, SensorData& sensorData );

    private:
        std::size_t size_;
        T* data_;
        T* dataStart_;
        T* dataEnd_;
    };

    template<class T, size_t sizeT>
    SensorData<T, sizeT>::SensorData():
    size_(sizeT),
    data_(new T[sizeT]),
    dataStart_(data_),
    dataEnd_(data_)
    {

    }

    template<class T, size_t sizeT>
    SensorData<T, sizeT>::SensorData(T *data):
    size_(sizeT)
    {
        data_ = new T[size_];
        std::copy(data, data+sizeof(T)*size_, data_);
        dataStart_ = data_;
        dataEnd_ = dataStart_ + sizeof(T)*size_;
    }

    template<class T, size_t sizeT>
    SensorData<T, sizeT>::~SensorData() {
        delete data_;
    }

    template<class T, size_t sizeT>
    void SensorData<T, sizeT>::resize(std::size_t newSize) noexcept(false) {

    }

    template<class T, size_t sizeT>
    SensorData<T, sizeT> &SensorData<T, sizeT>::operator=(SensorData &&other) noexcept {
        return *this;
    }

    template<class T, size_t sizeT>
    std::ostream &operator<<(std::ostream &o, SensorData<T, sizeT> &sensorData) {
        size_t end = sensorData.getSize();
        o << "{";
        for(int i = 0; i<end; ++i)
            o << sensorData[i] << (i != end-1 ? ", ": "}");
        return o;
    }

    template<class T, size_t sizeT>
    size_t SensorData<T, sizeT>::getSize() {
        return size_;
    }

    template<class T, size_t sizeT>
    T *SensorData<T, sizeT>::begin() {
        return data_[0];
    }

    template<class T, size_t sizeT>
    T *SensorData<T, sizeT>::end() {
        return data_[size_-1];
    }

    template<class T, size_t sizeT>
    void SensorData<T, sizeT>::push_back(T &&data) {
        
    }

    template<class T, size_t sizeT>
    size_t SensorData<T, sizeT>::size() {

        //   data_[]----data_[size_]
        size_t i;
        size_t end = 0;
        bool foundEnd = false;
        for(i = 0; i<size_; ++i){
            if(!foundEnd){
                if(&dataStart_[i] == &data_[size_])
                    end = i; foundEnd = true;
                if(&dataStart_ == &dataEnd_)
                    break;

            }else{
                if(&data_[i-end] == dataEnd_)
                    break;
            }
        }
        return i;
    }

    template<class T, size_t sizeT>
    T SensorData<T, sizeT>::pop() {
        return nullptr;
    }

}




#endif //ITAPK_EXAM_SENSORDATA_H
