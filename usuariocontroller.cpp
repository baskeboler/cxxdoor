#include "usuariocontroller.h"
#include <chrono>
#include <folly/Synchronized.h>
#include <folly/Singleton.h>

using namespace folly;

namespace cxxdoor {
static std::string map_key = "CXX_MAP_KEY";

namespace {
struct UsuarioControllerTag {};
}

static Singleton<UsuarioController, UsuarioControllerTag> the_instance;

UsuarioController::UsuarioController() {
  auto locked = _usuarios.lock();
  _db = DbManager::getInstance();
  _db->load<UserMap>(map_key, *locked, false);
}

UsuarioController::~UsuarioController() {
  auto locked = _usuarios.lock();
  _db->save<UserMap>(map_key, *locked, false);
}

bool UsuarioController::crearUsuario(std::string nombre, std::string password,
                                     std::string email) {
 auto locked = _usuarios.lock();
  auto found = locked->find(nombre);
  if (found == locked->end()) {
    auto user = std::make_shared<Usuario>();
    user->setNombre(nombre);
    user->setPassword(md5(password));
    user->setEmail(email);
    user->setId(RocksEntity::generateId());
    locked->emplace(std::make_pair(std::string(nombre), user));
    return true;
  }
  return false;
}

boost::optional<std::shared_ptr<TokenInfo>>
UsuarioController::authenticate(std::string nombre, std::string password) {
  auto locked = _usuarios.lock();
  auto result = locked->find(nombre);
  if (result != locked->end()) {
    auto user = result->second;//(*locked[nombre];
    if (user->getPassword() == md5(password)) {
      auto tokens = _tokens.lock();
      auto t = std::make_shared<TokenInfo>(RocksEntity::generateId(), user);
      tokens->emplace(std::make_pair(std::string(t->token), t));
      return t;
    }
  }
  return boost::none;
}

std::shared_ptr<UsuarioController>
UsuarioController::getInstance() {
  return the_instance.try_get();
}

std::string UsuarioController::md5(std::string message) {
  CryptoPP::Weak::MD5 hash;
  byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];
  hash.CalculateDigest(digest, reinterpret_cast<const byte *>(message.c_str()),
                       message.length());

  CryptoPP::HexEncoder encoder;
  std::string output;
  encoder.Attach(new CryptoPP::StringSink(output));
  encoder.Put(digest, sizeof(digest));
  encoder.MessageEnd();

  return output;
}
TokenInfo::TokenInfo(const std::string &token, const std::shared_ptr<Usuario> &usuario)
    : token(token), usuario(usuario), timestamp(std::chrono::system_clock::now()) {

}
}
