//
// Created by victor on 15/10/17.
//

#include "HandlerFactory.h"
#include <folly/Memory.h>


#include <boost/algorithm/string.hpp>
#include "UsuarioHandler.h"
#include <proxygen/httpserver/filters/RejectConnectFilter.h>

using boost::starts_with;
using std::string;

namespace cxxdoor {

}