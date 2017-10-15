//
// Created by victor on 15/10/17.
//
#include "BookingController.h"
#include "usuariocontroller.h"
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace cxxdoor;
using namespace boost::gregorian;

TEST(BookingController, getinstance) {
    auto c = BookingController::getInstance();
}

TEST(BookingController, create) {
    auto c = BookingController::getInstance();
    date d(from_simple_string("2018-1-1"));
    date_duration duration(2);
    bool res = c->insertSlot("user1", d, duration);
    EXPECT_FALSE(c->isSlotAvailable(d, duration));
}