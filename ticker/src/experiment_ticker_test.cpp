#include <thread>
#include <ticker/curlpp_request.hpp>
#include <ticker/parse_response.hpp>

using namespace CTAT;

int main() {

  for (auto i = 0; i < 2; i++) {

    CurlRequest request_;
    auto str = request_.getResponseString();

    if (str) {
      printAll(str->size());
      DataHandler handler;
      handler.constructAndQueryJson(*str);
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
  }



  return 0;
}