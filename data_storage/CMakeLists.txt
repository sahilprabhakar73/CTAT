find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
    message("Found SQLITE3")
endif(SQLITE3_FOUND)


include_directories(
    include/
    ${SQLite3_INCLUDE_DIRS}
)



add_executable(test_sqlite3 src/test_sqlite3.cpp)
target_link_libraries(test_sqlite3 ${SQLite3_LIBRARIES})