#pragma once

#include <curlpp/Easy.hpp>
#include <optional>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <ticker/utility.hpp>

namespace CTAT {

class CurlRequest {

public:
  CurlRequest(){};

  std::unique_ptr<curlpp::Easy> constructCurlppObject();

  std::optional<std::string>
  getResponseString(const std::unique_ptr<curlpp::Easy> &handler);

  void runOperation();

private:
  template <typename CurlOption>
  void setCurlppOption(curlpp::Easy &request, const CurlOption &option){
    request.setOpt(option);
  }

  template <typename... CurlOption>
  void setCurlppOptions(curlpp::Easy &request, const CurlOption &...option);

  // curlpp::Easy request_handler_;
  // std::unique_ptr<curlpp::Easy> request_handler_;
  const std::string TICKER_URL = "https://api.coindcx.com/exchange/ticker";
  const int RESPONSE_OK = 200;
  std::ostringstream response_stream;

  std::ofstream my_file_;
};

} // namespace CTAT