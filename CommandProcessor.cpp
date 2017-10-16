//
// Created by victor on 15/10/17.
//

#include <folly/dynamic.h>
#include <folly/json.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include "CommandProcessor.h"
#include "usuariocontroller.h"

using namespace proxygen;

namespace cxxdoor {

void CommandProcessor::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
  if (_body) {
    _body->prependChain(std::move(body));
  } else {
    _body = std::move(body);
  }
}
CommandProcessor::CommandProcessor(proxygen::ResponseHandler *downstream) : _downstream(downstream) {

}
}