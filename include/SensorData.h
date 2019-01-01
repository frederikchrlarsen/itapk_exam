//
// Created by frederik on 12/27/18.
//

#ifndef ITAPK_EXAM_SENSORDATA_H
#define ITAPK_EXAM_SENSORDATA_H

#include <algorithm>
#include <ostream>
#include <iostream>

#define MAX_MEMORY 2048


namespace apk{
    template<class T, std::size_t sizeT>
    class SensorData {

    public:

        typedef T value_type;

        SensorData();

        explicit SensorData(T data[]);

        ~SensorData();

        void resize(std::size_t newSize) noexcept(false);

        size_t getSize() const;

        T* begin();

        T* begin() const;

        T* end();

        T* end() const;

        void push_back(T &&data);
        void push_back(T &data);
        
        size_t size();

        T pop();

        //Copy constructor
        SensorData(const SensorData &obj);

        //Copy assignment operator
        SensorData& operator=(const SensorData& other) {
            std::cout << __PRETTY_FUNCTION__  << std::endl;
            return *this = SensorData(other);
        };

        //Move assignment operator
        SensorData& operator=(SensorData&& other) noexcept{
            return *this;
        };

        T& operator[](int i) {
            return data_[i];
        }

        template<T, size_t>
        friend std::ostream& operator<< ( std::ostream& o, SensorData& sensorData );

    private:

        T* nextPosEnd() const;
        T* nextPosStart();

        std::size_t size_;
        T* data_;
        T* dataStart_;
        T* dataEnd_;
        bool isEmpty_ = true;
    };

    template<class T, size_t sizeT>
    SensorData<T, sizeT>::SensorData():
    size_(sizeT),
    data_(new T[sizeT]),
    dataStart_(data_),
    dataEnd_(data_)
    {
        std::cout << "Constructor" << std::endl;
    }

    template<class T, size_t sizeT>
    SensorData<T, sizeT>::SensorData(T *data):
    size_(sizeT)
    {
        std::cout << "Constructor" << std::endl;
        data_ = new T[size_];
        std::copy(data, data+size_, data_);
        dataStart_ = data_;
        dataEnd_ = dataStart_ + size_;
    }

    template<class T, size_t sizeT>
    SensorData<T, sizeT>::SensorData(const SensorData &obj):
            size_(obj.getSize())
    {
        std::cout << "Copy constructor" << std::endl;
        data_ = new T[size_];
        std::copy(obj.begin(), obj.end(), data_);

    }

    template<class T, size_t sizeT>
    SensorData<T, sizeT>::~SensorData() {
        std::cout << "Destructor" << std::endl;
        delete[] data_;
    }

    template<class T, size_t sizeT>
    void SensorData<T, sizeT>::resize(std::size_t newSize) noexcept(false) {

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
    size_t SensorData<T, sizeT>::getSize() const {
        return size_;
    }

    template<class T, size_t sizeT>
    T *SensorData<T, sizeT>::begin() {
        return data_;
    }

    template<class T, size_t sizeT>
    T* SensorData<T, sizeT>::end() {
        return &data_[size_];
    }

    template<class T, size_t sizeT>
    void SensorData<T, sizeT>::push_back(T &&data) {

        if((dataEnd_  == dataStart_) && !isEmpty_ || (dataEnd_ == end()) && (dataStart_ == data_))
            throw std::runtime_error("No more space in SensorData");

        *dataEnd_ = data;
        isEmpty_ = false;

        dataEnd_ = nextPosEnd();
    }

    template<class T, size_t sizeT>
    void SensorData<T, sizeT>::push_back(T &data) {

        if((dataEnd_  == dataStart_) && !isEmpty_ || (dataEnd_ == end()) && (dataStart_ == data_))
            throw std::runtime_error("No more space in SensorData");

        *dataEnd_ = data;
        isEmpty_ = false;

        dataEnd_ = nextPosEnd();
    }

    template<class T, size_t sizeT>
    size_t SensorData<T, sizeT>::size() {

        //   data_[]----data_[size_]
        size_t i;
        size_t end = 0;
        bool foundEnd = false;
        for(i = 0; i<size_; ++i){
            if(!foundEnd){
                if((dataStart_+i) == (data_+size_)){
                    end = i;
                    foundEnd = true;
                }
                if(dataStart_ == dataEnd_){
                    if(!isEmpty_)
                        return size_;
                    break;
                }

            }else{
                if(&data_[i-end-1] == dataEnd_)
                    break;
            }
        }
        return i;
    }

    template<class T, size_t sizeT>
    T SensorData<T, sizeT>::pop() {
        if(isEmpty_)
            throw std::runtime_error("No more space in SensorData");
        T* before = dataStart_;
        dataStart_ = nextPosStart();
        return *(before);

    }

    template<class T, size_t sizeT>
    T *SensorData<T, sizeT>::begin() const {
        return data_;
    }

    template<class T, size_t sizeT>
    T *SensorData<T, sizeT>::end() const {
        return &data_[size_];
    }

    template<class T, size_t sizeT>
    T *SensorData<T, sizeT>::nextPosEnd() const {
        if(dataEnd_ + 1 == end())
            return data_;
        return dataEnd_ + 1;
    }

    template<class T, size_t sizeT>
    T *SensorData<T, sizeT>::nextPosStart() {
        if(dataStart_ + 1 == end()){
            if(data_ == dataEnd_)
                isEmpty_ = true;
            return data_;
        }
        if(dataStart_ + 1 == dataEnd_)
            isEmpty_ = true;
        return dataStart_ + 1;
    }

}




#endif //ITAPK_EXAM_SENSORDATA_H
