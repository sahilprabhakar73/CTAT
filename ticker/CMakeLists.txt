# find packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(CURLPP REQUIRED curlpp)
find_package(nlohmann_json REQUIRED)

# include dirs
include_directories(
    include/
)

# build executable 
add_executable(experiment_ticker

    src/curlpp_request.cpp
    # src/datahandler_base.cpp
    src/datahandler_cdcx.cpp
    src/experiment_ticker_test.cpp
)

target_link_libraries(experiment_ticker
    ${CURLPP_LDFLAGS}
    nlohmann_json::nlohmann_json
)


