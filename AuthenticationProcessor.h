//
// Created by victor on 16/10/17.
//

#ifndef CXXDOOR_AUTHENTICATIONPROCESSOR_H
#define CXXDOOR_AUTHENTICATIONPROCESSOR_H
#include <proxygen/httpserver/ResponseHandler.h>

#include "CommandProcessor.h"

namespace cxxdoor {

class AuthenticationProcessor : public CommandProcessor {
 public:
  AuthenticationProcessor(proxygen::ResponseHandler *downstream);
  virtual ~AuthenticationProcessor();
  virtual void onEOM() noexcept override;

 private:
};
}

#endif //CXXDOOR_AUTHENTICATIONPROCESSOR_H
