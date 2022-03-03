#include "ticker/datahandler_cdcx.hpp"
#include <iostream>
#include <mutex>
#include <sqlite3.h>
#include <string>
#include <tuple>

namespace CTAT {

// std::apply for tuples.

class DatabaseOperation {
public:
  DatabaseOperation() {}
  DatabaseOperation(const std::string &db_path) : db_path_(db_path) {}
  ~DatabaseOperation() = default;

  int callback(void *, int argc, char **argv, char **col_names); 
  // bool createDatabase();
  // bool createTable();

  template <typename... TupleData>
  std::string createInsertString(const std::string &table_name,
                                 const std::tuple<TupleData...> &data) {
    using std::get, std::to_string;

    std::string insert_string =
        "INSERT INTO " + table_name +
        "(ASK,BID,CHANGE_24_H,HIGH,LAST_PRICE,LOW,TIMESTAMP,VOLUME)"
        "VALUES(" +
        to_string(get<attr::ask>(data)) + "," +
        to_string(get<attr::bid>(data)) + "," +
        to_string(get<attr::change_24_hour>(data)) + "," +
        to_string(get<attr::high>(data)) + "," +
        to_string(get<attr::last_price>(data)) + "," +
        to_string(get<attr::low>(data)) + "," + get<attr::timestamp>(data) +
        "," + to_string(get<attr::volume>(data)) + ")";

  // timestamp attribute is already a string
    return insert_string;
  }

  std::string createTableFormat(
      const std::string
          &table_name); // no need to write the same format again and again.


  // a custom deleter is required incase we are to make unique_ptr for the
  // sqlite database object.
  //   https://stackoverflow.com/questions/45214238/c-smart-pointers-confusion
  

private:
  const std::string DEFAULT_DATABASE = "";
  const std::string db_path_;


  //   std::lock_guard<std::mutex> db_lock; // since we plan to add concurrency
  //   in here. this will help to resolve any conflict.
};

} // namespace CTAT
