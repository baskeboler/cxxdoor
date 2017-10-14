#include "usuario.h"
namespace cxxdoor {

Usuario::Usuario()  {}

std::string Usuario::getNombre() const { return nombre; }

void Usuario::setNombre(const std::string &value) { nombre = value; }

std::string Usuario::getEmail() const { return email; }

void Usuario::setEmail(const std::string &value) { email = value; }

std::string Usuario::getPassword() const { return password; }

void Usuario::setPassword(const std::string &value) { password = value; }

Usuario::~Usuario() {}

std::ostream &operator<<(std::ostream &os, const Usuario &c) {
    os << "usuario(" << c.getId() << ", " << c.getEmail() << ", " << c.getNombre()
       << ", " << c.getPassword() << ")";
    return os;
}

}
