//
// Created by victor on 16/10/17.
//

#include "AddUserProcessor.h"
#include "usuariocontroller.h"
#include <folly/dynamic.h>
#include <folly/json.h>
#include <proxygen/httpserver/ResponseBuilder.h>

namespace cxxdoor {
AddUserProcessor::AddUserProcessor(proxygen::ResponseHandler *downstream) : CommandProcessor(downstream) {}
void AddUserProcessor::onEOM() noexcept {
  auto s = _body->moveToFbString();

  auto obj = folly::parseJson(s);

  std::string nombre = obj["username"].asString();
  std::string password = obj["password"].asString();
  std::string email = obj["email"].asString();

  bool res = UsuarioController::getInstance()->crearUsuario(nombre, password, email);

  if (res) {
    proxygen::ResponseBuilder(_downstream)
        .status(201, "Created")
        .sendWithEOM();
  } else {
    proxygen::ResponseBuilder(_downstream)
        .status(500, "Error creando usuario").sendWithEOM();
  }
}
AddUserProcessor::~AddUserProcessor() =default;

}
