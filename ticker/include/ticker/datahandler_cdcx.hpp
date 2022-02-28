#pragma once
#include <ticker/datahandler_base.hpp>

namespace CTAT {

class DataCdcx : protected DataHandler {

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

public:
  DataCdcx(const std::vector<std::string> &query_vector)
      : DataHandler(TICKER_URL), query_(query_vector) {}

  void constructAndQueryJson(const std::string &response_string) override;

  template <typename... DataInput>
  auto stringToActualDataTypes(const std::tuple<DataInput...> &json_data);

  void fetchResponseAndParse();

private:
  std::vector<std::string> query_;
  const std::string TICKER_URL = "https://api.coindcx.com/exchange/ticker";
};

} // namespace CTAT