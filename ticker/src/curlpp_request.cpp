#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <memory>
#include <sstream>
#include <ticker/curlpp_request.hpp>

namespace CTAT {

std::unique_ptr<curlpp::Easy> CurlRequest::constructCurlppObject() {
  using namespace curlpp;
  auto request_handler = std::make_unique<curlpp::Easy>();

  setCurlppOptions(
      *request_handler, options::Url(TICKER_URL),
      options::WriteStream(&response_stream),
      options::WriteFunction(
          [](char *data, size_t size, size_t nmemb) { return size * nmemb; }),
      options::Verbose(true));
      
  return request_handler;
}

std::optional<std::string> CurlRequest::getResponseString(const std::unique_ptr<curlpp::Easy>& handler) {

  

  std::optional<std::string> response_string;
  if (curlpp::infos::ResponseCode::get(*handler) == RESPONSE_OK) {
    response_string = response_stream.str();
    return response_string;
  }
  return std::nullopt;
}

template <typename... CurlOption>
void CurlRequest::setCurlppOptions(curlpp::Easy &request,
                                  const CurlOption &...option) {
  (request.setOpt(option),...);
}


} // namespace CTAT