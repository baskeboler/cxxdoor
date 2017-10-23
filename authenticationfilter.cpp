#include "authenticationfilter.h"

namespace cxxdoor {


std::chrono::system_clock::duration AuthenticationFilter::token_expiry=std::chrono::minutes(6);
}
