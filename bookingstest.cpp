//
// Created by victor on 15/10/17.
//
#include "BookingController.h"
#include "usuariocontroller.h"
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <boost/random/random_number_generator.hpp>

using namespace cxxdoor;
using namespace boost::gregorian;


void randomBookings() {

    boost::random::uniform_int_distribution<> gen1(0, 365*2);
    boost::random::uniform_int_distribution<> gen2(1, 20);
    boost::random::mt11213b rng;

    auto ctrl = UsuarioController::getInstance();
    auto ctrl2 = BookingController::getInstance();
    for (int i=0; i < 2000; i++) {

        date start = boost::gregorian::day_clock::local_day() +  boost::gregorian::days(gen1(rng) );
        date end = start + boost::gregorian::days(gen2(rng));
        const auto &user = ctrl->getUsuario("user1").get();
        if (ctrl2->isSlotAvailable(start, end - start)) {
            DLOG(INFO) << "slot available";
            ctrl2->insertSlot(user->getNombre(), start,  end - start );
        } else {
            DLOG(INFO) << "slot not available";
        }

    }

}

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

TEST(BookingController, massive) {
    randomBookings();
}
