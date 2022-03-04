#include <data_storage/database_operation_cdcx.hpp>
#include <ticker/datahandler_cdcx.hpp>
namespace CTAT {

std::string
DatabaseOperationCdcx::createTableString(const std::string &table_name) {
  std::string gen_table_format = "CREATE TABLE IF NOT EXISTS " + table_name +
                                 "(" +
                                 "ASK DOUBLE,"
                                 "BID DOUBLE,"
                                 "CHANGE_24_H DOUBLE,"
                                 "HIGH DOUBLE,"
                                 "LAST_PRICE DOUBLE,"
                                 "LOW DOUBLE,"
                                 "TIMESTAMP TEXT,"
                                 "VOLUME DOUBLE);";

  return gen_table_format;
}

std::string DatabaseOperationCdcx::createInsertString(const TickerTuple &data) {
  using std::get, std::to_string;
  // accessing the non first tuple element is problematic, so figure out how to
  // do so with table_name
  std::string insert_string =
      "INSERT INTO " + get<attr::market>(data) /*table_name*/ +
      "(ASK,BID,CHANGE_24_H,HIGH,LAST_PRICE,LOW,TIMESTAMP,VOLUME)"
      "VALUES(" +
      to_string(get<attr::ask>(data)) + "," + to_string(get<attr::bid>(data)) +
      "," + to_string(get<attr::change_24_hour>(data)) + "," +
      to_string(get<attr::high>(data)) + "," +
      to_string(get<attr::last_price>(data)) + "," +
      to_string(get<attr::low>(data)) + "," + get<attr::timestamp>(data) + "," +
      to_string(get<attr::volume>(data)) + ")";

  // timestamp attribute is already a string
  return insert_string;
}

} // namespace CTAT