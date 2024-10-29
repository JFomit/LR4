#ifndef INCLUDE_LIB_ARRAY2D_H_
#define INCLUDE_LIB_ARRAY2D_H_

#include <cstddef>

namespace ctoast {
template <typename T>
class Array2d {
 public:
  Array2d() = default;
  virtual ~Array2d() = default;
  Array2d(Array2d &&other) noexcept = default;
  virtual Array2d &operator=(Array2d<T> &&other) noexcept = default;

  [[nodiscard]] virtual size_t width() const = 0;
  [[nodiscard]] virtual size_t height() const = 0;

  virtual const T &operator[](size_t i, size_t j) const = 0;
  virtual T &operator[](size_t i, size_t j) = 0;
};

template <typename T, size_t M, size_t N>
class StaticArray2d : public Array2d<T> {
 public:
  using array_t = T[M][N];

  StaticArray2d(const array_t &array) { array_ = (T *)array; }

  StaticArray2d(StaticArray2d &&other) noexcept : array_(other.array_) {
    other.array_ = nullptr;
  }

  StaticArray2d &operator=(StaticArray2d &&other) noexcept {
    if (&other != this) {
      array_ = other.array_;
      other.array_ = nullptr;
    }
    return *this;
  }

  [[nodiscard]] size_t width() const override { return M; }
  [[nodiscard]] size_t height() const override { return N; }

  const T &operator[](size_t i, size_t j) const override {
    return array_[i * height() + j];
  }
  T &operator[](size_t i, size_t j) override {
    return array_[i * height() + j];
  }

 private:
  T *array_;
};
}  // namespace ctoast

#endif  // INCLUDE_LIB_ARRAY2D_H_