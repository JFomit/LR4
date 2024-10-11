#ifndef INCLUDE_LIB_META_H_
#define INCLUDE_LIB_META_H_

#include <functional>
#include <utility>
#include <variant>

namespace ctoast {

template <typename E, typename T, typename U>
std::variant<E, U> bind(std::variant<E, T> result,
                        std::function<std::variant<E, U>(T)> function) {
  if (std::holds_alternative<E>(result)) {
    return std::variant<E, U>(std::get<E>(result));
  }

  return function(std::get<T>(result));
}

template <typename E, typename T, typename R>
R match(std::variant<E, T> result, std::function<R(T)> ok,
        std::function<R(E)> error) {
  if (std::holds_alternative<T>(result)) {
    return ok(std::get<T>(result));
  } else {
    return error(std::get<E>(result));
  }
}

// An alias for std::bind to diffirinciate from real ctoast::bind
template <typename... Args>
auto curry(Args &&...args) -> decltype(std::bind(std::forward<Args>(args)...)) {
  return std::bind(std ::forward<Args>(args)...);
}
}  // namespace ctoast

#endif  // INCLUDE_LIB_META_H_
