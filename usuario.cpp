#include "usuario.h"
namespace cxxdoor {

Usuario::Usuario() = default;

std::string Usuario::getNombre() const { return nombre; }

void Usuario::setNombre(const std::string &value) { nombre = value; }

std::string Usuario::getEmail() const { return email; }

void Usuario::setEmail(const std::string &value) { email = value; }

std::string Usuario::getPassword() const { return password; }

void Usuario::setPassword(const std::string &value) { password = value; }

folly::dynamic Usuario::get_json() const {
  return folly::dynamic::object("nombre", nombre)("email", email)("password",
                                                                  password);
}

std::ostream &operator<<(std::ostream &os, const Usuario &c) {
  os << "usuario(" << c.getId() << ", " << c.getEmail() << ", " << c.getNombre()
     << ", " << c.getPassword() << ")";
  return os;
}
Usuario::Usuario(Usuario &&other) :
    RocksEntity(std::move(other)), nombre(nullptr), email(nullptr), password(nullptr) {
  nombre = other.nombre;
  email = other.email;
  password = other.password;
  other.nombre = nullptr;
  other.email = nullptr;
  other.password = nullptr;

}

}
