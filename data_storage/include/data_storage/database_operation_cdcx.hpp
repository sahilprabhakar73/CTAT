#include <data_storage/database_operation_base.hpp>

namespace CTAT{

    class DatabaseOperationCdcx: protected DatabaseOperationBase{

        DatabaseOperationCdcx(const std::string& db_): DatabaseOperationBase(db_){} 

        std::string createTableFormat(const std::string& table_name) override;

        bool createTable(const std::string& table_name) override;

        
        template<typename...TupleData>
        std::string createInsertString(const std::tuple<TupleData...>& data){

        }



    };



} // namespace CTAT