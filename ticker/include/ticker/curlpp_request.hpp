#pragma once

#include <curlpp/Easy.hpp>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <ticker/utility.hpp>

namespace CTAT {

class CurlRequest {

public:
  CurlRequest(const std::string &url) : ticker_url_(url) {}

  bool constructCurlppObject();

  std::optional<std::string> getResponseString();

private:
  template <typename CurlOption>
  void setCurlppOption(curlpp::Easy &request, const CurlOption &option) {
    request.setOpt(option);
  }

  template <typename... CurlOption>
  void setCurlppOptions(curlpp::Easy &request, const CurlOption &...option) {
    (setCurlppOption(request, option), ...);
  }

  std::unique_ptr<curlpp::Easy> request_handler_;
  const std::string ticker_url_;
  const int RESPONSE_OK = 200;
  std::ostringstream response_stream;
  std::ofstream my_file_;
};

} // namespace CTAT