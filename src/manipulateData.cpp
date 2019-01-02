

//
// Created by Jens on 28-12-2018.
//

#include "manipulateData.h"
#include <Sensor.h>
#include <Subscriber.h>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <numeric>
#include<cstdio>
#include<cstdlib>

//using namespace std::placeholders;

int manipulateData::amountOfAttachedSubscribers;
int manipulateData::amountOfManipulateDataObjects;

void manipulateData::addSubscriber(apk::Subscriber *subscriber) {
    //std::cout << "Adding subscriber to manipulateData: " << subscriber << std::endl;

    this->subscriber.push_back(subscriber);
    amountOfAttachedSubscribers++;;
}

void manipulateData::removeSubscriber(apk::Subscriber *subscriber) {
    //std::cout << "Removing subscriber from manipulateData: " << subscriber << std::endl;
    this->subscriber.remove(subscriber);
    amountOfAttachedSubscribers--;;
}

void manipulateData::forEach() {

    std::for_each(subscriber.begin(), subscriber.end(),[](apk::Subscriber* & subscriber)
    {
        std::cout<<subscriber->getId() << std::endl;
    });
}

void manipulateData::copy(manipulateData *man_) {

    std::copy(subscriber.begin(), subscriber.end(), man_->subscriber.begin());
}


void manipulateData::bind_to_for_each()
{
    boost::function<void()> for_each_function( boost::bind( &manipulateData::forEach, this));
    for_each_function();

    //Hvis std::bind vil bruges i stedet - læs om forskellene her: https://www.boost.org/doc/libs/1_69_0/libs/bind/doc/html/bind.html#bind.purpose.overloaded_operators_new_in_boos
    //Om function: https://theboostcpplibraries.com/boost.function
/*
    std::function<void()> for_each_function = std::bind(&manipulateData::forEach, this);
    for_each_function();
*/

}

void manipulateData::accumulate()
{
    std::list<std::string> checkAccumulation;
    transformAllIDsToString(checkAccumulation);

}

void manipulateData::transformAllIDsToString(std::list<std::string> checkAccumulation) {

    std::string tmp_2;
    std::vector<int> VectorOfNumbersInId;

    std::transform(subscriber.begin(), subscriber.end(), checkAccumulation.begin(), [tmp_2](apk::Subscriber* &subscriber_)
            mutable -> std::string
    {
        tmp_2 += boost::lexical_cast<std::string>(subscriber_->getId());
        return tmp_2;
    });

    std::string accumulatedIdInString = checkAccumulation.back();

    for (char &it : accumulatedIdInString) {
        if(isdigit(it))
        {
            VectorOfNumbersInId.push_back(static_cast<int>(it));
        }
    }
    accumulatedId = std::accumulate(VectorOfNumbersInId.begin(), VectorOfNumbersInId.end(), 0);
    std::cout << accumulatedId << std::endl;
}
