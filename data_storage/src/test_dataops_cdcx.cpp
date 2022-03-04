#include <data_storage/database_operation_cdcx.hpp>
#include <ticker/utility.hpp>
using namespace CTAT;

int main(){

    auto ops_ptr = std::make_unique<DatabaseOperationCdcx>("/home/mach3/CTAT/data_storage/database/sample_database.db");
    printAll(ops_ptr->createTableString("ETHINR"));
    printAll(ops_ptr->createInsertString(std::make_tuple(12.0, 13.0, 14.0, 15.0, 16.0, 17.0,
                 std::string("MARKETINR"), std::string("TIMESTAMP_DATE"), 18.0)));

    return 0;
}