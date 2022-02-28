#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <memory>
#include <sstream>
#include <ticker/curlpp_request.hpp>

namespace CTAT {

bool CurlRequest::constructCurlppObject() {
  using namespace curlpp;
  request_handler_ = std::make_unique<curlpp::Easy>();

  // found the bug.
  // why the request returned with the size 0.
  // whenever we place the callback function after the response stream, for some
  // reason the response size becomes zero and that caused quite a lot of
  // trouble for couple of days.

  setCurlppOptions(
      *request_handler_,
      options::WriteFunction(
          [](char *data, size_t size, size_t nmemb) { return size * nmemb; }),
      options::Url(ticker_url_), options::WriteStream(&response_stream),
      options::Verbose(false));

  return true;
}

std::optional<std::string> CurlRequest::getResponseString() {

  if (constructCurlppObject()) {
    request_handler_->perform();

    std::optional<std::string> response_string;
    if (curlpp::infos::ResponseCode::get(*request_handler_) == RESPONSE_OK) {
      response_string = response_stream.str();
      return response_string;
    }
  }

  return std::nullopt;
}


} // namespace CTAT