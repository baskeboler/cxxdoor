#include "usuariocontroller.h"
#include <folly/Singleton.h>
namespace cxxdoor {
std::string UsuarioController::map_key = "CXX_MAP_KEY";

namespace {
struct UsuarioControllerTag {};
}

static folly::Singleton<UsuarioController, UsuarioControllerTag> the_instance;

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
