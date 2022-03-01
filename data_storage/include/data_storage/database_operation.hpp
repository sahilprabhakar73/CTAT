#include <iostream>
#include <mutex>
#include <sqlite3.h>
#include <string>
#include <tuple>

namespace CTAT {

class DatabaseOperation {
public:
  DatabaseOperation();
  DatabaseOperation(const std::string &db_path) : db_path_(db_path) {}
  ~DatabaseOperation() = default;

  int callback();

  bool createDatabase();
  bool createTable();

  template<typename... TupleData>
  std::string createInsertString(const std::tuple<TupleData...>& data);

  std::string createTableFormat(
      const std::string
          &table_name); // no need to write the same format again and again.

  // a custom deleter is required incase we are to make unique_ptr for the
  // sqlite database object.

  //   https://stackoverflow.com/questions/45214238/c-smart-pointers-confusion
  struct sqlDeleter {
    void operator()(sqlite3 *sql) {
      // sqlite3_close(sql);
      sqlite3_close_v2(sql); // what's the difference here ?
    }
  };

private:
  const std::string DEFAULT_DATABASE = "";
  const std::string db_path_;
  //   std::lock_guard<std::mutex> db_lock; // since we plan to add concurrency
  //   in here. this will help to resolve any conflict.
};

} // namespace CTAT
