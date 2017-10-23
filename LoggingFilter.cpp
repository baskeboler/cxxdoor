//
// Created by victor on 17/10/17.
//

#include "LoggingFilter.h"
#include <proxygen/lib/utils/Logging.h>
#include <glog/logging.h>

namespace cxxdoor {
LoggingFilter::LoggingFilter(proxygen::RequestHandler *upstream) : Filter(upstream) {}
void LoggingFilter::setResponseHandler(proxygen::ResponseHandler *handler) noexcept {
  Filter::setResponseHandler(handler);
}
void LoggingFilter::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers)   noexcept {
  LOG(INFO) << "Got headers";
  headers->getHeaders().forEach([](const auto &s1, const auto &s2) {
    LOG(INFO) << s1 << ": " << s2;
  });
  Filter::onRequest(std::move(headers));
}
void LoggingFilter::onBody(std::unique_ptr<folly::IOBuf> body)  noexcept {
  auto b = body->clone();
  LOG(INFO) << proxygen::IOBufPrinter::printChainInfo(b.get());
  LOG(INFO) << proxygen::IOBufPrinter::printHexFolly(b.get());
  Filter::onBody(std::move(body));
}
void LoggingFilter::onUpgrade(proxygen::UpgradeProtocol protocol)  noexcept {
  Filter::onUpgrade(protocol);
}
void LoggingFilter::onEOM()  noexcept {
  Filter::onEOM();
}
void LoggingFilter::requestComplete()  noexcept {
  Filter::requestComplete();
}
void LoggingFilter::onError(proxygen::ProxygenError err) noexcept {
  Filter::onError(err);
}
void LoggingFilter::onEgressPaused()  noexcept {
  Filter::onEgressPaused();
}
void LoggingFilter::onEgressResumed()  noexcept {
  Filter::onEgressResumed();
}
void LoggingFilter::sendHeaders(proxygen::HTTPMessage &msg)  noexcept {
  Filter::sendHeaders(msg);
}
void LoggingFilter::sendChunkHeader(size_t len)  noexcept {
  Filter::sendChunkHeader(len);
}
void LoggingFilter::sendBody(std::unique_ptr<folly::IOBuf> body)  noexcept {
  LOG(INFO) << "Sending body";
  auto b = body->clone();
  LOG(INFO) << proxygen::IOBufPrinter::printChainInfo(b.get());
  LOG(INFO) << proxygen::IOBufPrinter::printHexFolly(b.get());
  Filter::sendBody(std::move(body));
}
void LoggingFilter::sendChunkTerminator()  noexcept {
  Filter::sendChunkTerminator();
}
void LoggingFilter::sendEOM()  noexcept {
  Filter::sendEOM();
}
void LoggingFilter::sendAbort()  noexcept {
  Filter::sendAbort();
}
void LoggingFilter::refreshTimeout()  noexcept {
  Filter::refreshTimeout();
}
void LoggingFilter::pauseIngress()  noexcept {
  Filter::pauseIngress();
}
void LoggingFilter::resumeIngress()  noexcept {
  Filter::resumeIngress();
}
proxygen::ResponseHandler *LoggingFilter::newPushedResponse(proxygen::PushHandler *handler)  noexcept {
  return Filter::newPushedResponse(handler);
}
const wangle::TransportInfo &LoggingFilter::getSetupTransportInfo() const noexcept {
  return Filter::getSetupTransportInfo();
}
void LoggingFilter::getCurrentTransportInfo(wangle::TransportInfo *tinfo) const noexcept {
  Filter::getCurrentTransportInfo(tinfo);
}

void LoggingFilterFactory::onServerStart(folly::EventBase *evb) noexcept {

}
void LoggingFilterFactory::onServerStop() noexcept {

}
proxygen::RequestHandler *LoggingFilterFactory::onRequest(proxygen::RequestHandler *handler,
                                                          proxygen::HTTPMessage *message) noexcept {
  return new LoggingFilter(handler);
}
}
