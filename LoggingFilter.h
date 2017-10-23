//
// Created by victor on 17/10/17.
//

#ifndef CXXDOOR_LOGGINGFILTER_H
#define CXXDOOR_LOGGINGFILTER_H

#include <proxygen/httpserver/Filters.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>

using proxygen::Filter;
namespace cxxdoor {

class LoggingFilter : public Filter {
 public:
  LoggingFilter(proxygen::RequestHandler *upstream);
  void setResponseHandler(proxygen::ResponseHandler *handler) noexcept override;
  void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers)noexcept override;
  void onBody(std::unique_ptr<folly::IOBuf> body)noexcept override;
  void onUpgrade(proxygen::UpgradeProtocol protocol) noexcept override;
  void onEOM()noexcept override;
  void requestComplete()noexcept override;
  void onError(proxygen::ProxygenError err)noexcept override;
  void onEgressPaused()noexcept override;
  void onEgressResumed()noexcept override;
  void sendHeaders(proxygen::HTTPMessage &msg)noexcept override;
  void sendChunkHeader(size_t len)noexcept override;
  void sendBody(std::unique_ptr<folly::IOBuf> body)noexcept override;
  void sendChunkTerminator() noexcept override;
  void sendEOM() noexcept override;
  void sendAbort() noexcept override;
  void refreshTimeout()noexcept override;
  void pauseIngress()noexcept override;
  void resumeIngress()noexcept override;
  proxygen::ResponseHandler *newPushedResponse(proxygen::PushHandler *handler)noexcept override;
  const wangle::TransportInfo &getSetupTransportInfo() const noexcept override;
  void getCurrentTransportInfo(wangle::TransportInfo *tinfo) const noexcept override;

};

class LoggingFilterFactory: public proxygen::RequestHandlerFactory {
 public:
  void onServerStart(folly::EventBase *evb) noexcept override;
  void onServerStop() noexcept override;
  proxygen::RequestHandler *onRequest(proxygen::RequestHandler *handler, proxygen::HTTPMessage *message) noexcept override;

};
}
#endif //CXXDOOR_LOGGINGFILTER_H
