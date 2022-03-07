#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <ticker/curlpp_request.hpp>

namespace CTAT {

using JsonIterator = nlohmann::basic_json<>::iterator;
using MatchIndexVector =
    std::vector<nlohmann::detail::iter_impl<const nlohmann::basic_json<>>>;

class DataHandler {
public:
  DataHandler(const std::string &url)
      : request_(std::make_unique<CurlRequest>(url)) {}

  virtual MatchIndexVector
  jsonQuery(const nlohmann::basic_json<> &response) = 0;

  template <typename... Data>
  std::tuple<Data...> jsonToTuple(const Data &...data) {
    return std::make_tuple(data...);
  }

  // protected:
  std::unique_ptr<CurlRequest> request_;
};

} // namespace CTAT