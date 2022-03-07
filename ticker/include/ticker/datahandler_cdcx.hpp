#pragma once
#include <ticker/datahandler_base.hpp>

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

using TickerTuple =
    std::tuple<double, double, double, double, double, double,
               std::basic_string<char>, std::basic_string<char>, double>;

class DataCdcx : public DataHandler {

public:
  DataCdcx(const std::vector<std::string> &query_vector)
      : DataHandler("https://api.coindcx.com/exchange/ticker"),
        query_(query_vector) {}

  MatchIndexVector jsonQuery(const nlohmann::basic_json<> &response) override;

  std::vector<TickerTuple>
  queryResponseToTuple(const std::string &response_string);

  template <typename... DataInput>
  auto stringToActualDataTypes(const std::tuple<DataInput...> &json_data);

  std::vector<TickerTuple> runTicker();

  std::vector<std::string> getQuery() { return query_; }

private:
  std::vector<std::string> query_;
};

} // namespace CTAT