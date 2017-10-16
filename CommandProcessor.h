//
// Created by victor on 15/10/17.
//

#ifndef CXXDOOR_COMMANDPROCESSOR_H
#define CXXDOOR_COMMANDPROCESSOR_H
#include <proxygen/httpserver/ResponseHandler.h>

namespace cxxdoor {

class CommandProcessor {
 public:
  CommandProcessor(proxygen::ResponseHandler *downstream);

  virtual void onEOM() noexcept = 0;
  virtual void onBody(std::unique_ptr<folly::IOBuf> body) noexcept;
  virtual ~CommandProcessor() {

  }
 protected:

  std::unique_ptr<folly::IOBuf> _body;
  proxygen::ResponseHandler *_downstream;
};


}

#endif //CXXDOOR_COMMANDPROCESSOR_H
