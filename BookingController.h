//
// Created by victor on 14/10/17.
//

#ifndef CXXDOOR_BOOKINGCONTROLLER_H
#define CXXDOOR_BOOKINGCONTROLLER_H

#include "booking.h"
#include "dbmanager.h"
#include "usuariocontroller.h"
#include <memory>
#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
namespace cxxdoor {

    class BookingController {
        typedef boost::gregorian::date date;
        typedef boost::gregorian::date_duration date_duration;
        typedef boost::gregorian::date_period date_period;
        typedef std::vector<std::shared_ptr<Booking>> BookingsVector;
        typedef std::map<std::string, BookingsVector> BookingsMap;
    public:
        static std::shared_ptr<BookingController> getInstance();

        BookingController();

        virtual ~BookingController();

        bool isSlotAvailable(const date &from, const date_duration &duration);
        bool insertSlot(const std::string &username, const date& from, const date_duration &duration) {
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
    private:
        BookingsMap _bookingsByUsername;
        BookingsVector _bookingsVector;
        std::shared_ptr<DbManager> _db;
        std::shared_ptr<UsuarioController> _usuarioController;
    };
}


#endif //CXXDOOR_BOOKINGCONTROLLER_H
