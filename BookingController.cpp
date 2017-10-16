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

        _db->load<BookingsVector>(bookings_vector_key, _bookingsVector, false);
        _db->load<BookingsMap>(bookings_map_key, _bookingsByUsername, false);
    }

    BookingController::~BookingController() {
        LOG(INFO) << "Destroying BookingController";
        _db->save<BookingsVector>(bookings_vector_key, _bookingsVector, false);
        _db->save<BookingsMap>(bookings_map_key, _bookingsByUsername, false);
    }
bool BookingController::insertSlot(const std::string &username,
                                   const BookingController::date &from,
                                   const BookingController::date_duration &duration) {
  auto user = _usuarioController->getUsuario(username);
  if (!user) throw std::domain_error("usuario no existe");
  if (isSlotAvailable(from, duration)) {
    auto booking = std::make_shared<Booking>();
    date_period p(from, duration);
    booking->setFrom(p.begin());
    booking->setTo(p.end());
    booking->setUsuario(user.get());
    booking->setId(RocksEntity::generateId());
    _bookingsVector.push_back(booking);
    _bookingsByUsername[booking->getUsuario()->getNombre()].push_back(booking);
    std::sort(_bookingsVector.begin(), _bookingsVector.end());

    return true;
  }
  return false;
}
}