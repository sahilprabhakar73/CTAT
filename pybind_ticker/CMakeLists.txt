find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
find_package(pybind11 REQUIRED)


# include dirs
include_directories(
    include/
    ../
)

file(GLOB source_ticker RELATIVE "ticker" "*.cpp")




pybind11_add_module(ticker_pybind
${source_ticker} 
src/ticker_pybind.cpp
)