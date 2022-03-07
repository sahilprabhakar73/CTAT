#include <thread>
#include <ticker/datahandler_base.hpp>
#include <ticker/datahandler_cdcx.hpp>

using namespace CTAT;

int main() {

  

  auto derived_ptr = std::make_unique<DataCdcx>(std::vector<std::string>{"MATICINR", "ETHINR","ADAINR", "BATINR", "BTCINR"});
  auto ticker_data = derived_ptr->runTicker();

  for(auto& id: ticker_data){
    printAll(std::get<attr::market>(id), std::get<attr::last_price>(id));
  }
  
  
  return 0;
}