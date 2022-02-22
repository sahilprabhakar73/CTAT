#include <curlpp/Easy.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <tuple>


// Need to review about the architecture of the project.
// i.e. when to save data, remove data etc. sql or no sql.

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

  // instead of using struct, we will be using tuple + enums.
  // more efficient than stucts, need to add the link to doc/code.
  template <typename... Data>
  std::tuple<Data...> jsonToTuple(const Data &...data) {
    return std::make_tuple(data...);
  }

  template<typename... DataInput>
  auto stringToActualDataTypes(const std::tuple<DataInput...>& json_data);


};
} // namespace CTAT