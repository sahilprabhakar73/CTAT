#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include <chrono>
#include <cstdint>
#include <ctime>

// for helpful printing and stuff.
// https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple

// std::decay
// template::metaprogramming.

namespace CTAT {

inline std::string epochToDateTime() {
  using namespace std::chrono;

  auto time_t = system_clock::to_time_t(system_clock::now());
  auto dt_format = std::localtime(&time_t);
  char buf[80];
  strftime(buf, sizeof(buf), "%m/%d/%Y %H:%M:%S", dt_format);

  return std::string(buf); // format would be shown as above.
}

// https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time/31105859#31105859
// std::decay_t is important in order to convert from reference pointer to
// normal objects and much more than that.

// need to extend this for further stl containers as well.
namespace is_stl_container_impl {
template <typename T> struct is_stl_container : std::false_type {};
template <typename... Args>
struct is_stl_container<std::vector<Args...>> : std::true_type {};
} // namespace is_stl_container_impl

template <typename T> struct is_stl_container {
  static constexpr bool const value =
      is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
};

template <typename... VarTypes> void printAll(const VarTypes &...vars) {

  // if(is_stl_container<VarTypes...>::value){
  //   for(const auto& val: vars){

  //   }
  // }

  ((std::cout << vars << std::endl), ...);
}

} // namespace CTAT