//
// Created by victor on 16/10/17.
//

#ifndef CXXDOOR_ADDUSERPROCESSOR_H
#define CXXDOOR_ADDUSERPROCESSOR_H

#include "CommandProcessor.h"
namespace cxxdoor {

class AddUserProcessor : public CommandProcessor{
 public:
  AddUserProcessor(proxygen::ResponseHandler *downstream);
  void onEOM() noexcept override;
  virtual ~AddUserProcessor();
};

}

#endif //CXXDOOR_ADDUSERPROCESSOR_H
