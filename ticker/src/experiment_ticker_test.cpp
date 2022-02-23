#include <thread>
#include <ticker/curlpp_request.hpp>
#include <ticker/parse_response.hpp>

using namespace CTAT;

int main() {

  

  for (auto i = 0; i < 4; i++) {

    CurlRequest request_;

    request_.runOperation();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    //   if (response_string) {
    //     std::cout << *response_string << std::endl;

    //     // DataHandler handler;
    //     // handler.constructAndQueryJson(*response_string);
    //   }
  }

  // CurlRequest request_;
  // auto response_string = request_.getResponseString();

  // if (response_string) {
  //   std::cout << *response_string << std::endl;

  //   // DataHandler handler;
  //   // handler.constructAndQueryJson(*response_string);
  // }

  return 0;
}