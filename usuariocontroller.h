#ifndef USUARIOCONTROLLER_H
#define USUARIOCONTROLLER_H

#include "dbmanager.h"
#include "usuario.h"
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/optional.hpp>
#include <folly/Synchronized.h>
#include <folly/AtomicHashMap.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <crypto++/hex.h>
#include <crypto++/md5.h>
#include <boost/optional.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <chrono>
using boost::gregorian::date;
namespace cxxdoor {

struct TokenInfo {
  std::string token;
  std::chrono::system_clock::time_point timestamp;
  std::shared_ptr<Usuario> usuario;
  TokenInfo(const std::string &token, const std::shared_ptr<Usuario> &usuario);
};

class UsuarioController {

 public:

  typedef std::map<std::string, std::shared_ptr<Usuario>> UserMap;
  typedef std::map<std::string, std::shared_ptr<TokenInfo>> TokenMap;
  UsuarioController();

  ~UsuarioController();

  bool crearUsuario(std::string nombre, std::string password,
                    std::string email = "");

  boost::optional<std::shared_ptr<TokenInfo>> authenticate(std::string nombre, std::string password);

  static std::shared_ptr<UsuarioController> getInstance();

  std::string md5(std::string message);

  boost::optional<std::shared_ptr<Usuario>> getUsuario(std::string username) {
    auto locked = _usuarios.lock();
    auto found = locked->find(username);
    if (found != locked->end()) {
      return found->second;
    }
    return boost::none;
  }

 private:
  std::shared_ptr<DbManager> _db;
  folly::Synchronized<UserMap, boost::mutex> _usuarios;
  folly::Synchronized<TokenMap, boost::mutex> _tokens;
};
}

#endif // USUARIOCONTROLLER_H
