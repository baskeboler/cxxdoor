// Created by victor on 15/10/17.
//
//

#include "UsuarioHandler.h"
#include <proxygen/httpserver/ResponseBuilder.h>
#include "AuthenticationProcessor.h"
using std::string;
using namespace proxygen;

namespace cxxdoor {

void UsuarioHandler::onRequest(std::unique_ptr<HTTPMessage> headers) noexcept {
  const string path = headers->getPath();
  DLOG(INFO) << "handling onRequest: " << path;
  if (path == "/user/authenticate" && headers->getMethodString() == "POST") {
    _commandProcessor = std::make_shared<AuthenticationProcessor>(this->downstream_);
  } else {

    ResponseBuilder(downstream_).status(500, "Could not handle request")
        .sendWithEOM();
  }
}

void UsuarioHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
  DLOG(INFO) << "handling onBody";
  if (_commandProcessor)
    _commandProcessor->onBody(std::move(body));
}

void UsuarioHandler::onUpgrade(UpgradeProtocol prot) noexcept {
  DLOG(INFO) << "handling onUpgrade";
}

void UsuarioHandler::onEOM() noexcept {
  DLOG(INFO) << "handling onEOM";
  if (_commandProcessor)
    _commandProcessor->onEOM();
}

void UsuarioHandler::requestComplete() noexcept {
  DLOG(INFO) << "handling requestComplete";
  delete this;
}

void UsuarioHandler::onError(ProxygenError err) noexcept {
  DLOG(INFO) << "handling onError";
  delete this;
}
UsuarioHandler::~UsuarioHandler() {

}
void UsuarioHandler::setResponseHandler(ResponseHandler *handler) noexcept {
  RequestHandler::setResponseHandler(handler);
}
void UsuarioHandler::onEgressPaused() noexcept {
  RequestHandler::onEgressPaused();
}
void UsuarioHandler::onEgressResumed() noexcept {
  RequestHandler::onEgressResumed();
}
UsuarioHandler::UsuarioHandler() {}

}