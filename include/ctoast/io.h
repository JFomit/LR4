#ifndef INCLUDE_LIB_TERMINAL_H_
#define INCLUDE_LIB_TERMINAL_H_

#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <variant>

namespace ctoast {

template <typename T>
using CinResult = std::variant<std::string, T>;

template <typename T>
CinResult<T> ReadT(const char *error_str) {
  T value{};

  std::cin >> value;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return CinResult<T>(error_str);
  }

  if (!std::cin.eof() && std::cin.peek() != '\n') {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return CinResult<T>(error_str);
  }

  return CinResult<T>(value);
}

template <typename T>
CinResult<T> Read() {
  return ReadT<T>("Некорректный ввод");
}

template <typename T>
CinResult<T> Read(const char *error_str) {
  return ReadT<T>(error_str);
}

template <>
CinResult<double> Read();
template <>
CinResult<int> Read();
template <>
CinResult<char> Read();
template <>
CinResult<long> Read();

template <typename T>
void Print(T value, const char *prompt) {
  std::cout << prompt << value;
}

template <typename T>
void PrintLine(T value, const char *prompt) {
  std::cout << prompt << value << '\n';
}

void PrintLine(const std::string &str);
}  // namespace ctoast

#endif  // INCLUDE_LIB_TERMINAL_H_
