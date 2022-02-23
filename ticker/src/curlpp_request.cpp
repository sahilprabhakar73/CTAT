#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <memory>
#include <sstream>
#include <ticker/curlpp_request.hpp>

namespace CTAT {

std::unique_ptr<curlpp::Easy> CurlRequest::constructCurlppObject() {
  using namespace curlpp;

  auto request = std::make_unique<curlpp::Easy>();

  setCurlppOptions(
      *request,
      options::WriteFunction(
          [](char *data, size_t size, size_t nmemb) { return size * nmemb; }),
      options::Url(TICKER_URL), options::WriteStream(&response_stream),
      options::Verbose(false));

  // found the bug.
  // why the request returned with the size 0.
  // whenever we place the callback function after the response stream, for some
  // reason the response size becomes zero and that caused quite a lot of
  // trouble for couple of days.

  return request;
}

std::optional<std::string>
CurlRequest::getResponseString(const std::unique_ptr<curlpp::Easy> &handler) {

  std::optional<std::string> response_string;
  if (curlpp::infos::ResponseCode::get(*handler) == RESPONSE_OK) {
    response_string = response_stream.str();
    std::cout << "RESPONSE_OK"
              << " " << response_string->size() << std::endl;
    return response_string;
  }
  return std::nullopt;
}

void CurlRequest::runOperation() {

  auto request = constructCurlppObject();
  response_stream.clear();
  request->perform();
  auto resp = getResponseString(request);

  if (resp) {
    // printAll(*resp);
    my_file_.open("/home/mach3/example.txt",
                  std::ios::out | std::ios::binary | std::ios_base::app);
    my_file_ << *resp << "\n";
    my_file_.close();
  }
}

template <typename... CurlOption>
void CurlRequest::setCurlppOptions(curlpp::Easy &request,
                                   const CurlOption &...option) {
  (setCurlppOption(request, option), ...);
}

} // namespace CTAT