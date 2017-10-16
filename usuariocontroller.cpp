#include "usuariocontroller.h"
#include <folly/Singleton.h>
namespace cxxdoor {
static std::string map_key = "CXX_MAP_KEY";

namespace {
struct UsuarioControllerTag {};
}

static folly::Singleton<UsuarioController, UsuarioControllerTag> the_instance;

UsuarioController::UsuarioController() {
  _db = DbManager::getInstance();
  _db->load<UserMap>(map_key, _usuarios, false);
}

UsuarioController::~UsuarioController() {
  _db->save<UserMap>(map_key, _usuarios, false);
}

bool UsuarioController::crearUsuario(std::string nombre, std::string password,
                                     std::string email) {
  auto found = _usuarios.find(nombre);
  if (found == _usuarios.end()) {
    auto user = std::make_shared<Usuario>();
    user->setNombre(nombre);
    user->setPassword(md5(password));
    user->setEmail(email);
    user->setId(RocksEntity::generateId());
    _usuarios[nombre] = user;
    return true;
  }
  return false;
}

bool UsuarioController::authenticate(std::string nombre, std::string password) {
  auto result = _usuarios.find(nombre);
  if (result != _usuarios.end()) {
    auto user = _usuarios[nombre];
    return user->getPassword() == md5(password);
  }
  return false;
}

std::shared_ptr<cxxdoor::UsuarioController>
cxxdoor::UsuarioController::getInstance() {
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
}
