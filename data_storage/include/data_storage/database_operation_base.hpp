#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include <mutex>
#include <sqlite3.h>

namespace CTAT {

class DatabaseOperationBase {
public:
  enum operation { CREATE_TABLE = 0, INSERT_DATA, QUERY_DATA };

  // custom deleter to be used along with std::unique_ptr;
  struct SqliteDeleter {
    void operator()(sqlite3 *sql) { sqlite3_close_v2(sql); }
  };

  // scope_exit class to cleanup after sqlite C char allocs and many more.
  template <typename F> struct ScopeExit {
    F f_;

    explicit ScopeExit(F f) noexcept : f_(std::move(f)) {}
    ScopeExit(ScopeExit &&rhs) noexcept : f_((rhs.f_)) {}
    ~ScopeExit() { f_(); }

    // deleted copy/move constructors.
    ScopeExit &operator=(ScopeExit &&rhs) = delete;
    ScopeExit(ScopeExit const &) = delete;
    ScopeExit &operator=(ScopeExit const &) = delete;
  };

  // type-aliasing for convenience.
  using sqlite_ptr = std::unique_ptr<sqlite3, SqliteDeleter>;

  DatabaseOperationBase(const std::string &db_name) : database_path(db_name) {}

  std::unique_ptr<sqlite3, SqliteDeleter> createSqlitePtr(char const *db_name);

  static int callback(void *, int argc, char **argv, char **col_names);

  virtual std::string createTableString(const std::string &tablename) = 0;
  
  bool executeSqlOperation(const std::string &sql_statement,
                           enum operation oper);

protected:
  std::mutex db_lock;
  const std::string database_path;
  const std::string DEFAULT_PATH = " ";

private:
};

} // namespace CTAT