#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>


// std::decay
// template::metaprogramming.

namespace CTAT {
// https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time/31105859#31105859
// std::decay_t is important in order to convert from reference pointer to normal objects and much more than that.


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
  
  // ((std::cout << vars << std::endl), ...);
}   


} // namespace CTAT