#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <ticker/curlpp_request.hpp>

namespace CTAT {

class DataHandler {

public:
  DataHandler(const std::string &url)
      : request_(std::make_unique<CurlRequest>(url)) {}

  virtual void constructAndQueryJson(const std::string &response_string) = 0;

  template <typename... Data>
  std::tuple<Data...> jsonToTuple(const Data &...data) {
    return std::make_tuple(data...);
  }

protected:
  std::unique_ptr<CurlRequest> request_;
};

} // namespace CTAT