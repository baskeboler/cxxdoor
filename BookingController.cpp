//
// Created by victor on 14/10/17.
//

#include "BookingController.h"
#include <folly/Singleton.h>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <glog/logging.h>
#include <boost/date_time/gregorian/gregorian_io.hpp>

namespace cxxdoor {
    namespace {
        struct BookingControllerTag {};
    }
    static folly::Singleton<BookingController, BookingControllerTag> the_instance;
    std::shared_ptr<BookingController> BookingController::getInstance() {
        return the_instance.try_get();
    }

    bool BookingController::isSlotAvailable(const BookingController::date &from, const BookingController::date_duration &duration) {
        date_period slot(from, duration);
        LOG(INFO) << "Checking slot availability: " << slot;

        for (auto &b: _bookingsVector) {
            date_period p(b->getFrom(), b->getTo());
            if (p.intersects(slot)) {
                LOG(INFO) << slot << " intersects with " << p;
                return false;
            }
        }
        return true;
    }

    static std::string bookings_vector_key = "CXXDOOR_BOOKINGS_VECTOR";
    static std::string bookings_map_key = "CXXDOOR_BOOKINGS_MAP";

    BookingController::BookingController() {
        LOG(INFO) << "Initializing BookingController";
        _db = DbManager::getInstance();
        _usuarioController = UsuarioController::getInstance();

        _db->load<BookingsVector>(bookings_vector_key, _bookingsVector);
        _db->load<BookingsMap>(bookings_map_key, _bookingsByUsername);
    }

    BookingController::~BookingController() {
        LOG(INFO) << "Destroying BookingController";
        _db->save<BookingsVector>(bookings_vector_key, _bookingsVector);
        _db->save<BookingsMap>(bookings_map_key, _bookingsByUsername);
    }
}