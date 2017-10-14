#ifndef USUARIO_H
#define USUARIO_H

#include "rocksentity.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <string>
namespace cxxdoor {

class Usuario : public RocksEntity {
  friend boost::serialization::access;
  friend std::ostream &operator<<(std::ostream &os, const Usuario &c);

public:
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &boost::serialization::base_object<RocksEntity>(*this);
    ar &nombre &email &password;
  }
  Usuario();

  std::string getNombre() const;
  void setNombre(const std::string &value);

  std::string getEmail() const;
  void setEmail(const std::string &value);

  std::string getPassword() const;
  void setPassword(const std::string &value);

  virtual ~Usuario();

private:
  std::string nombre;
  std::string email;
  std::string password;

  // RocksEntity interface
public:
  folly::dynamic get_json() const override {
    return folly::dynamic::object("nombre", nombre)("email", email)("password",
                                                                    password);
  }
};

}

#endif // USUARIO_H
