//
// Created by victor on 15/10/17.
//

#ifndef CXXDOOR_USUARIOHANDLER_H
#define CXXDOOR_USUARIOHANDLER_H
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/lib/utils/StateMachine.h>
#include "CommandProcessor.h"
//#include <folly/Memory.h>

namespace cxxdoor {

class UsuarioHandler : public proxygen::RequestHandler {
 public:
  UsuarioHandler();
  void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers)noexcept override;

  void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

  void onUpgrade(proxygen::UpgradeProtocol prot)noexcept override;

  void onEOM()noexcept override;

  void requestComplete()noexcept override;

  void onError(proxygen::ProxygenError err)noexcept override;

  virtual ~UsuarioHandler();
  void setResponseHandler(proxygen::ResponseHandler *handler) noexcept override;
  void onEgressPaused() noexcept override;
  void onEgressResumed()noexcept  override;
 private:
  std::shared_ptr<CommandProcessor> _commandProcessor{nullptr};
};
}

#endif //CXXDOOR_USUARIOHANDLER_H
