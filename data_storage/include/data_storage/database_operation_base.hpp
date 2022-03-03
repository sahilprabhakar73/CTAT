#include <iostream>
#include <memory>
#include <string>
#include <tuple>

#include <mutex>
#include <sqlite3.h>

namespace CTAT {

class DatabaseOperationBase {
public:
  DatabaseOperationBase(const std::string &db_name) : database_path(db_name) {}

  // custom deleter to be used along with std::unique_ptr;
  struct SqliteDeleter {
    void operator()(sqlite3 *sql) { sqlite3_close_v2(sql); }
  };

  // scope_exit class to cleanup after sqlite C char allocs and many more.
  // https://stackoverflow.com/questions/36644263/is-there-a-c-standard-class-to-set-a-variable-to-a-value-at-scope-exit
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

  int callback(void *, int argc, char **argv, char **col_names);

  virtual std::string createTableFormat(const std::string &tablename) = 0;

  virtual bool createTable(const std::string &tablename) = 0;

  // templated virtual functions are not feasible since the template <> is a
  // compile time and virtual function binds to the implementation of the
  // virtual function in run time. look up type_erasure c++, it's more of a
  // workaround.
  // or we still have this function limited to the __cdcx file while keeping
  // other things available template<typename... TupleData> virtual std::string
  // createInsertString(const std::tuple<TupleData...>& tuple_data);

protected:
  std::mutex db_lock;
  const std::string database_path;
  const std::string DEFAULT_PATH = " ";

private:
};

} // namespace CTAT