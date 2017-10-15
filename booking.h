#ifndef BOOKING_H
#define BOOKING_H

#include "rocksentity.h"
#include "usuario.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <memory>
namespace cxxdoor {

class Booking : public RocksEntity {
  friend boost::serialization::access;
  friend std::ostream& operator<<(std::ostream& os, const Booking& c);
public:
  Booking();
  virtual ~Booking() = default;

    template <class Archive>
  void serialize(Archive &ar, const unsigned int /* version */) {
    ar &boost::serialization::base_object<RocksEntity>(*this) &
        usuario &from &to;
  }

    bool operator<(const Booking &rhs) const;

    bool operator>(const Booking &rhs) const;

    bool operator<=(const Booking &rhs) const;

    bool operator>=(const Booking &rhs) const;

    bool operator==(const Booking &rhs) const;

    bool operator!=(const Booking &rhs) const;

private:
  std::shared_ptr<Usuario> usuario;
  boost::gregorian::date from;
  boost::gregorian::date to;

  // RocksEntity interface
public:
  folly::dynamic get_json() const override;
  std::shared_ptr<Usuario> getUsuario() const;
  void setUsuario(const std::shared_ptr<Usuario> &value);
  boost::gregorian::date getFrom() const;
  void setFrom(const boost::gregorian::date &value);
  boost::gregorian::date getTo() const;
  void setTo(const boost::gregorian::date &value);
};
}

#endif // BOOKING_H
