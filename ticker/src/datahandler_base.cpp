#include <ticker/datahandler_base.hpp>

namespace CTAT {

DataHandler::DataHandler(const std::string &url)
    : request_(std::make_unique<CurlRequest>(url)) {

  // what else needs to be initialized. think about it.
}

} // namespace CTAT