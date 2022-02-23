#include <iostream>
#include <nlohmann/json.hpp>
#include <tuple>

namespace CTAT {

enum attr {
  ask = 0,
  bid,
  change_24_hour,
  high,
  last_price,
  low,
  market,
  timestamp,
  volume
};

class DataHandler {
public:
  DataHandler();

  void constructAndQueryJson(const std::string &response_string);

  void constructAndProcessAll(const std::string &response_string);

  template <typename... Data>
  std::tuple<Data...> jsonToTuple(const Data &...data) {
    return std::make_tuple(data...);
  }

  template <typename... DataInput>
  auto stringToActualDataTypes(const std::tuple<DataInput...> &json_data);

private:
  std::vector<std::string> query_;
};
} // namespace CTAT