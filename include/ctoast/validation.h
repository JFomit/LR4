#ifndef INCLUDE_LIB_VALIDATION_H_
#define INCLUDE_LIB_VALIDATION_H_

#include <functional>
#include "io.h"

namespace ctoast {
template <typename T>
std::function<CinResult<T>(T)> CreateIsInRange(
    T min, T max,
    std::string error_text = "Значение вне необходимого диапазона") {
  T minn = std::min(min, max);
  T maxx = std::max(min, max);
  return [=](T value) {
    return minn <= value && value <= maxx ? CinResult<T>(value)
                                          : CinResult<T>(error_text);
  };
}

template <typename T>
std::function<CinResult<T>(T)> CreateIsInRangeMinExclusive(
    T min, T max,
    std::string error_text = "Значение вне необходимого диапазона") {
  T minn = std::min(min, max);
  T maxx = std::max(min, max);
  return [=](T value) {
    return minn < value && value <= maxx ? CinResult<T>(value)
                                         : CinResult<T>(error_text);
  };
}
}  // namespace ctoast

#endif  // INCLUDE_LIB_VALIDATION_H_
