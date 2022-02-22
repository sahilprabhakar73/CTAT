#include <chrono>
#include <iostream>
#include <thread>
#include <ticker/curlpp_request.hpp>

int main() {

  CTAT::CurlRequest request_handler;
  auto request_ptr = request_handler.constructCurlppObject();

  for (auto i = 0; i < 3; i++) {
    request_ptr->perform();
    std::this_thread::sleep_for(std::chrono::seconds(20));

    std::cout << std::endl;
    std::cout << std::endl;

    auto str = request_handler.getResponseString(request_ptr);
    if (str) {
      std::cout << *str << std::endl;
    }
  }
  

  return 0;
}