#include <data_storage/database_operation_base.hpp>

namespace CTAT {

int DatabaseOperationBase::callback(void *, int argc, char **argv,
                                    char **col_names) {
  using std::cout, std::endl;

  for (int i = 0; i < argc; ++i)
    cout << col_names[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
  cout << endl;
  return 0;
}

// for some reason type alias was giving error.
std::unique_ptr<sqlite3, DatabaseOperationBase::SqliteDeleter>
DatabaseOperationBase::createSqlitePtr(const char *db_name) {

  sqlite3 *db;
  int err_msg = sqlite3_open(database_path.c_str(), &db);
  sqlite_ptr sql_ptr{db};

  if (err_msg) {
    std::cout << "Error [] returned: " << err_msg << std::endl;
    sql_ptr.reset();
  }

  return sql_ptr;
}

bool DatabaseOperationBase::executeSqlOperation(
    const std::string &sql_statement, enum operation oper) {

  auto tmp_ptr = createSqlitePtr(database_path.c_str());
  if (!tmp_ptr) {
    std::cout << "Error: " << sqlite3_errmsg(tmp_ptr.get()) << std::endl;
    return false;
  }
  char *error_msg;
  ScopeExit clear_error_msg{[&]() { sqlite3_free(error_msg); }};

  if (oper == operation::CREATE_TABLE || oper == operation::INSERT_DATA) {
    int err_msg = sqlite3_exec(tmp_ptr.get(), sql_statement.c_str(),
                               &DatabaseOperationBase::callback, 0, &error_msg);
    if (err_msg != SQLITE_OK) {
      return false;
    }
  }

  return true;
}

} // namespace CTAT