//
// Created by victor on 14/10/17.
//

#include "BookingController.h"
#include <folly/Singleton.h>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <glog/logging.h>
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <folly/Synchronized.h>
#include  "booking.h"

namespace cxxdoor {
namespace {
struct BookingControllerTag {};
}
static folly::Singleton<BookingController, BookingControllerTag> the_instance;
std::shared_ptr<BookingController> BookingController::getInstance() {
  return the_instance.try_get();
}

bool BookingController::isSlotAvailable(const BookingController::date &from,
                                        const BookingController::date_duration &duration) {
  date_period slot(from, duration);
  LOG(INFO) << "Checking slot availability: " << slot;
  auto locked = _bookingsVector.lock();
  for (auto b: *locked) {
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
  {
    auto locked1 = _bookingsVector.lock();
    auto locked2 = _bookingsByUsername.lock();
    _db->load<BookingsVector>(bookings_vector_key, *locked1, false);
    _db->load<BookingsMap>(bookings_map_key, *locked2, false);
  }
}

BookingController::~BookingController() {
  LOG(INFO) << "Destroying BookingController";

  auto locked1 = _bookingsVector.lock();
  auto locked2 = _bookingsByUsername.lock();
  _db->save<BookingsVector>(bookings_vector_key, *locked1, false);
  _db->save<BookingsMap>(bookings_map_key, *locked2, false);
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
    {
      auto bvector = _bookingsVector.lock();
      auto bmap = _bookingsByUsername.lock();

      bvector->push_back(booking);
      if (bmap->find(username) == bmap->end())
        bmap->emplace(std::make_pair(std::string(username), std::vector<std::shared_ptr<Booking>>()));
      bmap->at(username).push_back(booking);
      //_bookingsByUsername.lock()->emplace(std::make_pair(booking->getUsuario()->getNombre().push_back(booking);
      std::sort(bvector->begin(), bvector->end());
    }

    return true;
  }
  return false;
}
}