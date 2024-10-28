#ifndef INCLUDE_LIB_TERMINAL_H_
#define INCLUDE_LIB_TERMINAL_H_

#include <cstddef>
#include <expected>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include "ctoast/array.h"

namespace ctoast {

template <typename T>
using CinResult = std::expected<T, std::string>;

template <typename T>
CinResult<T> ReadT(const char *error_str) {
  T value{};

  std::cin >> value;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::unexpected(error_str);
  }

  if (!std::cin.eof() && std::cin.peek() != '\n') {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::unexpected(error_str);
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

template <typename T, size_t S>
CinResult<void> ReadArray(StaticArray<T, S> &buffer) {
  for (size_t i = 0; i < S; ++i) {
    auto result = Read<T>();

    if (result.has_value()) {
      buffer[i] = result.value();
    } else {
      return std::unexpected<std::string>(result.error());
    }
  }

  return {};
}

template <typename T>
CinResult<DynamicArray<T>> ReadArray(size_t size) {
  DynamicArray<T> arr = DynamicArray<T>(size);

  for (size_t i = 0; i < size; ++i) {
    auto result = Read<T>();
    if (result.has_value()) {
      arr[i] = result.value();
    } else {
      return std::unexpected(result.error());
    }
  }

  return CinResult<DynamicArray<T>>(arr);
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
