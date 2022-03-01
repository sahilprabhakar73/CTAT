#include "data_storage/database_operation.hpp"
#include "ticker/datahandler_cdcx.hpp"

namespace CTAT {

// need to do a base class with this otherwise it won't suffice having common
// functions all along. sqlite_orm (wrapper + object relation mapper) instead of
// C based sqlite3. https://github.com/fnc12/sqlite_orm/

// do string_view instead of string?

std::string
DatabaseOperation::createTableFormat(const std::string &table_name) {

  std::string gen_table_format = "CREATE TABLE IF NOT EXISTS " + table_name +
                                 "(" +
                                 "ASK DOUBLE"
                                 "BID DOUBLE"
                                 "CHANGE_24_H DOUBLE"
                                 "HIGH DOUBLE"
                                 "LAST_PRICE DOUBLE"
                                 "LOW DOUBLE"
                                 "TIMESTAMP TEXT"
                                 "VOLUME DOUBLE);";

  return gen_table_format;
}

template <typename... TupleData>
std::string
DatabaseOperation::createInsertString(const std::tuple<TupleData...> &data) {
  using std::get, std::to_string;

  std::string insert_string =
      "INSERT INTO " + get<attr::market>(data) +
      "(ASK,BID,CHANGE_24_H,HIGH,LAST_PRICE,LOW,TIMESTAMP,VOLUME)"
      "VALUES(" +
      to_string(get<attr::ask>(data)) + "," + to_string(get<attr::bid>(data)) +
      "," + to_string(get<attr::change_24_hour>(data)) + "," +
      to_string(get<attr::high>(data)) + "," +
      to_string(get<attr::last_price>(data)) + "," +
      to_string(get<attr::low>(data)) + "," +
      to_string(get<attr::timestamp>(data)) + "," +
      to_string(get<attr::volume>(data)) + ")";

  return insert_string;
}

} // namespace CTAT