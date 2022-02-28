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


void DataCdcx::constructAndQueryJson(const std::string &response) {
  auto response_json = nlohmann::json::parse(response);

  // function to find the matches required
  auto find_matches = [&response_json](const std::vector<std::string> &query) {
    using namespace nlohmann;
    std::vector<detail::iter_impl<basic_json<>>> match_index;

    for (const auto &queryname : query) {

      auto match =
          std::find_if(std::begin(response_json), std::end(response_json),
                       [&queryname](const auto &response) {
                         return response["market"] == queryname;
                       });
      match_index.emplace_back(match);

      printAll(*match);
      
    }

    
    return match_index;
  };

  // iterate through the matches and convert the data to some type.
  for (const auto &match : find_matches(query_)) {

    auto dcx_data = stringToActualDataTypes(jsonToTuple(
        (*match)["ask"].get<std::string>(), (*match)["bid"].get<std::string>(),
        (*match)["change_24_hour"].get<std::string>(),
        (*match)["high"].get<std::string>(),
        (*match)["last_price"].get<std::string>(),
        (*match)["low"].get<std::string>(),
        (*match)["market"].get<std::string>(),
        (*match)["timestamp"].get<long double>(),
        (*match)["volume"].get<std::string>()));

    // where to move this tuple or store this tuple now
    // to a database.
  }
}

void DataCdcx::fetchResponseAndParse(){
  auto response_string = request_->getResponseString();

  if(response_string){
    constructAndQueryJson(*response_string);
  }
  
}

} // namespace CTAT