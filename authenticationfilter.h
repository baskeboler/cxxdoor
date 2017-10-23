#ifndef AUTHENTICATIONFILTER_H
#define AUTHENTICATIONFILTER_H
#include <proxygen/httpserver/Filters.h>
#include <proxygen/lib/utils/CryptUtil.h>
#include <proxygen/httpserver/ResponseBuilder.h>
#include "usuariocontroller.h"

using proxygen::RequestHandler;
using proxygen::Filter;
using proxygen::ResponseBuilder;

#define CXXDOOR_AUTH_HEADER_NAME "CXXDOOR_TOKEN"

namespace cxxdoor {
class AuthenticationFilter : public Filter {
  static std::chrono::system_clock::duration token_expiry;

 public:
  explicit AuthenticationFilter(RequestHandler *upstream) :
      proxygen::Filter(upstream) {

  }
  virtual ~AuthenticationFilter();
  void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override {
    bool authHeaderIsPresent = headers->getHeaders().exists(CXXDOOR_AUTH_HEADER_NAME);
    if (authHeaderIsPresent) {
      auto token = headers->getHeaders().getSingleOrEmpty(CXXDOOR_AUTH_HEADER_NAME);
      auto valid = UsuarioController::getInstance()->validateToken(token);
      if (valid) {
        Filter::onRequest(std::move(headers));
        return;
      }
    }
    ResponseBuilder(downstream_)
        .status(403, "Unauthorized")
        .sendWithEOM();
  }
};
}
#endif /* AUTHENTICATIONFILTER_H */
