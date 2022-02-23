#include <algorithm>
#include <iterator>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <ticker/parse_response.hpp>
#include <tuple>
#include <vector>

namespace CTAT {

DataHandler::DataHandler() {}

template <typename... DataInput>
auto DataHandler::stringToActualDataTypes(
    const std::tuple<DataInput...> &json_data) {

  using std::get, std::stod;

  auto final_type = std::make_tuple(
      stod(get<attr::ask>(json_data)), stod(get<attr::bid>(json_data)),
      stod(get<attr::change_24_hour>(json_data)),
      stod(get<attr::high>(json_data)), stod(get<attr::last_price>(json_data)),
      stod(get<attr::low>(json_data)), get<attr::market>(json_data),
      stod(get<attr::timestamp>(json_data)),
      stod(get<attr::volume>(json_data)));

  return final_type;
}

void DataHandler::constructAndQueryJson(const std::string &response_string) {

  auto response_json = nlohmann::json::parse(response_string);
  std::vector<std::string> query{"ETHINR", "MATICINR"};

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
      std::cout << *match << std::endl;
      match_index.emplace_back(match);

      
    }
    return match_index;
  };

  for (const auto &match : find_matches(query)) {

    auto to_tuple = jsonToTuple((*match)["ask"].get<std::string>(),
                                (*match)["bid"].get<std::string>(),
                                (*match)["change_24_hour"].get<std::string>(),
                                (*match)["high"].get<std::string>(),
                                (*match)["last_price"].get<std::string>(),
                                (*match)["low"].get<std::string>(),
                                (*match)["market"].get<std::string>(),
                                (*match)["timestamp"].get<std::string>(),
                                (*match)["volume"].get<std::string>());
    std::cout << "Succesfully converted JSON Data to TUPLE" << std::endl;

    auto correct_tuple = stringToActualDataTypes(to_tuple);

    // from here, where do we send the correct tuple to ?
  }
}

} // namespace CTAT