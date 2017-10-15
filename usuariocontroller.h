#ifndef USUARIOCONTROLLER_H
#define USUARIOCONTROLLER_H
#include "dbmanager.h"
#include "usuario.h"
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <map>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/hex.h>
#include <crypto++/md5.h>

namespace cxxdoor {

class UsuarioController {
public:
  typedef std::map<std::string, std::shared_ptr<Usuario>> UserMap;
  UsuarioController() {
    _db = DbManager::getInstance();

    _db->load<UserMap>(map_key, _usuarios);
  }
  ~UsuarioController() { _db->save<UserMap>(map_key, _usuarios); }
  static std::shared_ptr<UsuarioController> getInstance();

  std::string md5(std::string message);

private:
  std::shared_ptr<DbManager> _db;
  UserMap _usuarios;
  static std::string map_key;
};
}

#endif // USUARIOCONTROLLER_H
