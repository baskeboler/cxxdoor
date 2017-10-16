//
// Created by victor on 16/10/17.
//

#include <folly/json.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include "AuthenticationProcessor.h"
#include "usuariocontroller.h"
#include <folly/dynamic.h>
#include <folly/json.h>
using namespace proxygen;

namespace cxxdoor {

AuthenticationProcessor::AuthenticationProcessor(ResponseHandler *downstream)
    : CommandProcessor(downstream) {}

void AuthenticationProcessor::onEOM() noexcept {

  folly::dynamic json = folly::parseJson(_body->moveToFbString());
  _body.reset();
  auto ctrl = UsuarioController::getInstance();
  auto result = ctrl->authenticate(json["username"].asString(), json["password"].asString());
  if (result) {
    folly::dynamic response = folly::dynamic::object("token", result->get()->token)
        ("username", result->get()->usuario->getNombre())
        ("timestamp", result->get()->timestamp.time_since_epoch().count());
    ResponseBuilder(_downstream)
        .status(200, "ok")
        .body(folly::toPrettyJson(response))
        .sendWithEOM();
  } else {
    ResponseBuilder(_downstream)
        .status(403, "Authentication failed")
        .sendWithEOM();
  }
}
AuthenticationProcessor::~AuthenticationProcessor() = default;
}