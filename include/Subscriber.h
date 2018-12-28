//
// Created by frederik on 12/21/18.
//

#ifndef ITAPK_EXAM_SUBSCRIBER_H
#define ITAPK_EXAM_SUBSCRIBER_H


#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>

namespace apk{

class Subscriber{

public:

    Subscriber():id(gen()){
        std::cout << "Created subscriber: " << boost::uuids::to_string(id) << std::endl;
    };

    void test(){
        std::cout << boost::uuids::to_string(id) << std::endl;
    }

    void dataCallback(float data){
        std::cout << "Subscriber (" << boost::uuids::to_string(id) << ") got data: " << data << std::endl;
    }

private:
    boost::uuids::random_generator gen;
    boost::uuids::uuid id;
};

}
#endif //ITAPK_EXAM_SUBSCRIBER_H
