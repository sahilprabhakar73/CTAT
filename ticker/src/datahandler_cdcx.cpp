#include <chrono>
#include <nlohmann/json.hpp>
#include <ticker/datahandler_cdcx.hpp>
#include <ticker/utility.hpp>

namespace CTAT {

template <typename... DataInput>
auto DataCdcx::stringToActualDataTypes(const std::tuple<DataInput...> &json) {
  using std::get, std::stod;

  // not converting the timestamp to DateTime as I couldn't find a solution but
  // there's no time discrepancy here though.
  auto converted_tuple = std::make_tuple(
      stod(get<attr::ask>(json)), stod(get<attr::bid>(json)),
      stod(get<attr::change_24_hour>(json)), stod(get<attr::high>(json)),
      stod(get<attr::last_price>(json)), stod(get<attr::low>(json)),
      get<attr::market>(json), epochToDateTime(),
      stod(get<attr::volume>(json)));

  return converted_tuple;
}

MatchIndexVector DataCdcx::jsonQuery(const nlohmann::basic_json<> &response) {

  MatchIndexVector indexes;

  for (const auto &index : query_) {
    indexes.emplace_back(std::find_if(
        std::begin(response), std::end(response),
        [&index](auto &match) { return match["market"] == index; }));
  }

  return indexes;
}

std::vector<TickerTuple>
DataCdcx::queryResponseToTuple(const std::string &response) {
  // request

  auto response_json = nlohmann::json::parse(response);
  auto matches = jsonQuery(response_json);

  std::vector<TickerTuple> tuple_holder;

  for (const auto &match : matches) {
    auto match_tuple = stringToActualDataTypes(jsonToTuple(
        (*match)["ask"].get<std::string>(), (*match)["bid"].get<std::string>(),
        (*match)["change_24_hour"].get<std::string>(),
        (*match)["high"].get<std::string>(),
        (*match)["last_price"].get<std::string>(),
        (*match)["low"].get<std::string>(),
        (*match)["market"].get<std::string>(),
        (*match)["timestamp"].get<long double>(),
        (*match)["volume"].get<std::string>()));

    tuple_holder.emplace_back(match_tuple);
  }

  return tuple_holder;
}

std::vector<TickerTuple> DataCdcx::runTicker() {

  auto response_string = request_->getResponseString();
  if (!response_string) {
    throw std::runtime_error("Curl Request yielded no response string");
  } else {
    auto ticker_tuple = queryResponseToTuple(*response_string);
    return ticker_tuple;
  }
}

} // namespace CTAT