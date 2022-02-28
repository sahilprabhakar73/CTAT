#include <thread>
#include <ticker/datahandler_base.hpp>
#include <ticker/datahandler_cdcx.hpp>

using namespace CTAT;

int main() {

  

  auto derived_ptr = std::make_unique<DataCdcx>(std::vector<std::string>{"MATICINR", "ETHINR"});
  derived_ptr->fetchResponseAndParse();
  
  return 0;
}