//
// Created by Bruger on 30-12-2018.
//

//
// Created by Jens on 28-12-2018.
//

#include "manipulateData.h"

//using namespace std::placeholders;

void manipulateData::addSubscriber(apk::Subscriber *subscriber) {
    //std::cout << "Adding subscriber to manipulateData: " << subscriber << std::endl;
    this->subscriber.push_back(subscriber);
}

void manipulateData::removeSubscriber(apk::Subscriber *subscriber) {
    //std::cout << "Removing subscriber from manipulateData: " << subscriber << std::endl;
    this->subscriber.remove(subscriber);
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

void manipulateData::clamp() {
}


void manipulateData::bind_to_for_each()
{
    boost::function<void()> for_each_function( boost::bind( &manipulateData::forEach, this));
    for_each_function();
}

void manipulateData::accumulate()
{
    transformAllIDsToString();

    std::string s = checkAccumulation.back();
    std::cout << s << std::endl;

    for (char &it : s) {
        if(isdigit(it))
        {
            VectorOfNumbersInId.push_back(static_cast<int>(it));
            //std::cout << static_cast<int>(*it);
            //std::cout << std::endl;
        }
    }
    accumulatedId = std::accumulate(VectorOfNumbersInId.begin(), VectorOfNumbersInId.end(), 0);
}

void manipulateData::transformAllIDsToString() {
    std::string tmp_2;
    std::string final_string_tmp_2;

    std::transform(subscriber.begin(), subscriber.end(), checkAccumulation.begin(), [tmp_2, final_string_tmp_2](apk::Subscriber *&subscriber_)
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