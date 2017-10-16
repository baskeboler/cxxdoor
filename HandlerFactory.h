//
// Created by victor on 15/10/17.
//

#ifndef CXXDOOR_HANDLERFACTORY_H
#define CXXDOOR_HANDLERFACTORY_H

#include <proxygen/httpserver/RequestHandlerFactory.h>
#include <folly/io/async/EventBaseManager.h>
#include <proxygen/httpserver/filters/RejectConnectFilter.h>
#include <boost/algorithm/string.hpp>
#include "UsuarioHandler.h"

using boost::starts_with;
using std::string;

namespace cxxdoor {

class HandlerFactory : public proxygen::RequestHandlerFactory {
 public:
  virtual void onServerStart(folly::EventBase *evb) noexcept {
    DLOG(INFO) << "onServerStart";
  }
  virtual void onServerStop() noexcept {

    DLOG(INFO) << "onServerStop";
  }
  virtual proxygen::RequestHandler *onRequest(proxygen::RequestHandler *handler,
                                              proxygen::HTTPMessage *message) noexcept {
    DLOG(INFO) << "onRequest";
    const string path = message->getPath();

    if (starts_with(path, "/user")) {
      DLOG(INFO) << "starts with /user";
      return new UsuarioHandler();
    }
    return new proxygen::RejectConnectFilter(handler);
  }
  virtual ~HandlerFactory() = default;
};

}

#endif //CXXDOOR_HANDLERFACTORY_H
