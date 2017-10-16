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
#include <boost/optional.hpp>

namespace cxxdoor {

    class UsuarioController {
    public:
        typedef std::map<std::string, std::shared_ptr<Usuario>> UserMap;

        UsuarioController();

        ~UsuarioController();

        bool crearUsuario(std::string nombre, std::string password,
                          std::string email = "");

        bool authenticate(std::string nombre, std::string password);

        static std::shared_ptr<UsuarioController> getInstance();

        std::string md5(std::string message);

        boost::optional<std::shared_ptr<Usuario>> getUsuario(std::string username) {
            auto found = _usuarios.find(username);
            if (found != _usuarios.end()) {
                return found->second;
            }
            return boost::none;
        }

    private:
        std::shared_ptr<DbManager> _db;
        UserMap _usuarios;
    };
}

#endif // USUARIOCONTROLLER_H
