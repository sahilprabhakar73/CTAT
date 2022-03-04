find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
    message("Found SQLITE3")
endif(SQLITE3_FOUND)


include_directories(
    include/
    ${SQLite3_INCLUDE_DIRS}
)


add_library(dataops_cdcx 
src/database_operation_base.cpp
src/database_operation_cdcx.cpp
)
target_link_libraries(dataops_cdcx PUBLIC ${SQLite3_LIBRARIES})


add_executable(test_dataops_cdcx
src/database_operation_base.cpp
src/database_operation_cdcx.cpp
src/test_dataops_cdcx.cpp
)
target_link_libraries(test_dataops_cdcx ${SQLite3_LIBRARIES})
