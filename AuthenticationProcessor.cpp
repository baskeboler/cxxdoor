//
// Created by victor on 16/10/17.
//

#include <folly/json.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include "AuthenticationProcessor.h"
#include "usuariocontroller.h"

using namespace proxygen;

namespace cxxdoor {

AuthenticationProcessor::AuthenticationProcessor(ResponseHandler *downstream)
    : CommandProcessor(downstream) {}

void AuthenticationProcessor::onEOM() noexcept {

  folly::dynamic json = folly::parseJson(_body->moveToFbString());
  _body.reset();
  auto ctrl = UsuarioController::getInstance();
  bool ok = ctrl->authenticate(json["username"].asString(), json["password"].asString());
  if (ok) {
    ResponseBuilder(_downstream)
        .status(200, "ok")
        .sendWithEOM();
  } else {
    ResponseBuilder(_downstream)
        .status(403, "Authentication failed")
        .sendWithEOM();
  }
}
AuthenticationProcessor::~AuthenticationProcessor() = default;
}