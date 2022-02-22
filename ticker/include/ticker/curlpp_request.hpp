#pragma once

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <optional>
#include <sstream>
#include <string>

namespace CTAT {

class CurlRequest {

public:
  CurlRequest() = default;

  std::unique_ptr<curlpp::Easy> constructCurlppObject();

  std::optional<std::string>
  getResponseString(const std::unique_ptr<curlpp::Easy> &handlers);

private:
  template <typename... CurlOption>
  void setCurlppOptions(curlpp::Easy &request, const CurlOption &...option);

  curlpp::Easy request_handler;
  const std::string TICKER_URL = "https://api.coindcx.com/exchange/ticker";
  const int RESPONSE_OK = 200;
  std::ostringstream response_stream;
};

} // namespace CTAT