

//
// Created by Jens on 28-12-2018.
//

#include "manipulateData.h"


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

void manipulateData::transform(manipulateData *man_) {

    std::transform(subscriber.begin(), subscriber.end(), man_->subscriber.begin(), [](apk::Subscriber* & subscriber_)
    {
        return subscriber_;
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
    transformAllIDsToString();

    accumulatedIdInString = checkAccumulation.back();
    //std::cout << accumulatedInString << std::endl;

    for (char &it : accumulatedIdInString) {
        if(isdigit(it))
        {
            VectorOfNumbersInId.push_back(static_cast<int>(it));
            //std::cout << static_cast<int>(*it);
            //std::cout << std::endl;
        }
    }
    accumulatedId = std::accumulate(VectorOfNumbersInId.begin(), VectorOfNumbersInId.end(), 0);
    std::cout << "Accumulated ID: " << accumulatedId << std::endl;
}

void manipulateData::transformAllIDsToString() {
    std::string tmp_2;

    std::transform(subscriber.begin(), subscriber.end(), checkAccumulation.begin(), [tmp_2](apk::Subscriber *&subscriber_)
            mutable -> std::string
    {
        tmp_2 += boost::lexical_cast<std::string>(subscriber_->getId());

        return tmp_2;
    });
}


void manipulateData::transformIdsToString() {
    std::string tmp;
    std::string final_string_tmp;

    std::transform(subscriber.begin(), subscriber.end(), idsInString.begin(), [tmp, final_string_tmp](apk::Subscriber* & subscriber_)
            mutable -> std::string
    {
        tmp = boost::lexical_cast<std::string>(subscriber_->getId());

        return tmp;
    });
}