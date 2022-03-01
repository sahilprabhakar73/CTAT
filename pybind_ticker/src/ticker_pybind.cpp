#include <ticker/curlpp_request.hpp>
#include <ticker/datahandler_base.hpp>
#include <ticker/datahandler_cdcx.hpp>
#include <ticker/utility.hpp>

#include <pybind11/pybind11.h>

namespace py = pybind11;

// current issue that exists.
// type info for class Dcx when we import it into python.

// possible issues with the cmakelists.txt for the pybind exporter or somethign.

namespace CTAT{

PYBIND11_MODULE(ticker_pybind, var){
    var.doc() = "Python binding for the Ticker module of CTAT.";
    
    py::class_<DataHandler>(var, "DataHandler");
    // .def(py::init<const std::string&>());
    

    py::class_<DataCdcx, DataHandler>(var, "DataCdcx")
    .def(py::init< const std::vector<std::string>& > ())
    .def_property("getQuery", &DataCdcx::getQuery, nullptr)
    .def("fetchResponseAndParse", &DataCdcx::fetchResponseAndParse);

    
}

}