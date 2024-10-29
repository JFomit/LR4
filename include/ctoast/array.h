#ifndef INCLUDE_LIB_ARRAY_H_
#define INCLUDE_LIB_ARRAY_H_

#include <cstddef>

namespace ctoast {
template <typename T>
class Array {
 public:
  Array() = default;
  virtual ~Array() = default;
  Array(Array &&other) noexcept = default;
  virtual Array &operator=(Array<T> &&other) noexcept = default;

  [[nodiscard]] virtual size_t size() const = 0;

  virtual const T &operator[](size_t index) const = 0;
  virtual T &operator[](size_t index) = 0;
};

template <typename T, size_t S>
class StaticArray : public Array<T> {
 public:
  using array_t = T[S];

  StaticArray(const array_t &array) : array_((T *)array) {}

  StaticArray(StaticArray &&other) noexcept : array_(other.array_) {
    other.array_ = nullptr;
  }

  StaticArray &operator=(StaticArray &&other) noexcept {
    if (&other != this) {
      array_ = other.array_;
      other.array_ = nullptr;
    }
    return *this;
  }

  [[nodiscard]] size_t size() const override { return S; }

  const T &operator[](size_t index) const override { return array_[index]; }
  T &operator[](size_t index) override { return array_[index]; }

 private:
  T *array_;
};

template <typename T>
class DynamicArray : public Array<T> {
 public:
  DynamicArray(size_t size) : size_(size), array_(new T[size]{}) {}

  DynamicArray(DynamicArray &&other) noexcept
      : size_(other.size_), array_(other.array_) {
    other.array_ = nullptr;
  }

  DynamicArray &operator=(DynamicArray &&other) noexcept {
    if (&other != this) {
      array_ = other.array_;
      size_ = other.size_;
      other.array_ = nullptr;
    }
    return *this;
  }

  ~DynamicArray() override { delete[] array_; }

  [[nodiscard]] size_t size() const override { return size_; }

  const T &operator[](size_t index) const override { return array_[index]; }

  T &operator[](size_t index) override { return array_[index]; }

 private:
  size_t size_;
  T *array_;
};
}  // namespace ctoast

#endif  // INCLUDE_LIB_ARRAY_H_