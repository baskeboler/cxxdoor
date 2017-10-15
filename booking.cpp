#include "booking.h"

namespace cxxdoor {

    std::ostream &operator<<(std::ostream &os, const Booking &c) {
        return os << "Booking( usuario: " << *c.getUsuario() << ", " << c.getFrom()
                  << ", " << c.getTo() << ")";
    }

    Booking::Booking() = default;

    folly::dynamic Booking::get_json() const {
        return folly::dynamic::object("id", getId())("usuario", usuario->get_json())(
                "from", boost::gregorian::to_iso_extended_string(from))(
                "to", boost::gregorian::to_iso_extended_string(to));
    }

    boost::gregorian::date Booking::getTo() const { return to; }

    void Booking::setTo(const boost::gregorian::date &value) { to = value; }

    boost::gregorian::date Booking::getFrom() const { return from; }

    void Booking::setFrom(const boost::gregorian::date &value) { from = value; }

    std::shared_ptr<Usuario> Booking::getUsuario() const { return usuario; }

    void Booking::setUsuario(const std::shared_ptr<Usuario> &value) {
        usuario = value;
    }

    bool Booking::operator<(const Booking &rhs) const {
        return from < rhs.from;
    }

    bool Booking::operator>(const Booking &rhs) const {
        return rhs < *this;
    }

    bool Booking::operator<=(const Booking &rhs) const {
        return !(rhs < *this);
    }

    bool Booking::operator>=(const Booking &rhs) const {
        return !(*this < rhs);
    }

    bool Booking::operator==(const Booking &rhs) const {
        return static_cast<const RocksEntity &>(*this) == static_cast<const RocksEntity &>(rhs) &&
               usuario == rhs.usuario &&
               from == rhs.from &&
               to == rhs.to;
    }

    bool Booking::operator!=(const Booking &rhs) const {
        return !(rhs == *this);
    }
}
