#include <data_storage/database_operation_base.hpp>

namespace CTAT {

class DatabaseOperationCdcx : protected DatabaseOperationBase {
public:
  // same format throughout, better use type alias instead of template.
  using TickerTuple =
      std::tuple<double, double, double, double, double, double,
                 std::basic_string<char>, std::basic_string<char>, double>;

  DatabaseOperationCdcx(const std::string &db_) : DatabaseOperationBase(db_) {}

  std::string createTableString(const std::string &table_name) override;

  std::string createInsertString(const TickerTuple &data);
};

} // namespace CTAT