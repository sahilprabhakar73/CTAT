#include <iostream>
#include <memory>
#include <sqlite3.h>
#include <string>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

struct sqlDeleter {
  void operator()(sqlite3 *sql) {
    // sqlite3_close(sql);
    sqlite3_close_v2(sql); // what's the difference here ?
  }
};



using unique_sqlite_ptr = std::unique_ptr<sqlite3, sqlDeleter>;
std::string insert_to_table(double str_ask, double str_bid, double str_change) {

  // auto return_exec = "INSERT INTO ETHINR (ASK,BID,CHANGE_24_H)"
  //                    "VALUES (3056.0, 3495.0, 1.047);";

  auto return_executable = "INSERT INTO ETHINR (ASK,BID,CHANGE_24_H)" \  
                           "VALUES (" +
                           std::to_string(str_ask) +  "," + std::to_string(str_bid) + "," +
                           std::to_string(str_change) + ");";

  std::cout << return_executable.c_str() << std::endl;
  return return_executable;
}

int main() {

  // unique_sqlite_ptr database_;

  sqlite3 *database;
  auto database_file =
      "/home/mach3/CTAT/data_storage/database/sample_database.db";

  // sqlite3_open(database_, &database);
  sqlite3_open(database_file, &database);
  sqlite3_close(database);

  // sqlite3_open(database_file, &database);

  std::string sql_create_table = "CREATE TABLE IF NOT EXISTS BTCINR("
                                 "ASK DOUBLE,"
                                 "BID DOUBLE,"
                                 "CHANGE_24_H DOUBLE);";

  // std::string sql_create_another_table = "CREATE TABLE IF NOT EXISTS ETHINR("
  //                                        "ASK DOUBLE,"
  //                                        "BID DOUBLE,"
  //                                        "CHANGE_24_H DOUBLE);";

  // std::string sql_insert_to_btc = "INSERT INTO BTCINR (ASK,BID,CHANGE_24_H)" \
  //                                 "VALUES (340056.0, 330495.0, 2.047);";

  std::string sql_insert_to_eth = "INSERT INTO ETHINR (ASK,BID,CHANGE_24_H)" \
                                  "VALUES (3056.0, 3495.0, 1.047);";

  std::cout << sql_insert_to_eth.c_str()  << std::endl;

  try {
    sqlite3_open(database_file, &database);
    char *messageError;
    // auto error = sqlite3_exec(database, sql_create_table.c_str(), NULL, 0,
    //                           &messageError);

    // auto error_new = sqlite3_exec(database, sql_create_another_table.c_str(),
    //                               NULL, 0, &messageError);

    // auto insert_btc = sqlite3_exec(database, sql_insert_to_btc.c_str(),
    //                                callback, 0, &messageError);

    auto insert_eth =
        sqlite3_exec(database, insert_to_table(66.5, 33, 6.7).c_str(), callback,
                     0, &messageError);

    sqlite3_close(database);

  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  // // updating the table

  return 0;
}