#include "ctoast/io.h"

namespace ctoast {
template <>
CinResult<double> Read() {
  return ReadT<double>("Ожидалось вещественное число");
}

template <>
CinResult<int> Read() {
  return ReadT<int>("Ожидалось целое число");
}

template <>
CinResult<char> Read() {
  return ReadT<char>("Ожидался символ");
}

template <>
CinResult<long> Read() {
  return ReadT<long>("Ожидалось челое число");
}

void PrintLine(const std::string &str) {
  std::cout << str << '\n';
}
}  // namespace ctoast