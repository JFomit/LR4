#ifndef LR4_TASK_3_APP_H_
#define LR4_TASK_3_APP_H_

#include <cstddef>
#include "ctoast/io.h"

namespace app {
// @remarks Firts index defines row, second - column
template <typename T>
class DynamicArrayOfArrays {
 public:
  DynamicArrayOfArrays(size_t width, size_t height, const T &initial = {}) {
    width_ = width;
    height_ = height;

    arrays_ = new T *[height_];
    for (size_t i = 0; i < height_; ++i) {
      arrays_[i] = new T[width_](initial);
    }
  }
  ~DynamicArrayOfArrays() { FreeBackingArrays(); }

  DynamicArrayOfArrays(const DynamicArrayOfArrays<T> &other) = delete;
  DynamicArrayOfArrays<T> &operator=(const DynamicArrayOfArrays<T> &rhs) =
      delete;

  DynamicArrayOfArrays(DynamicArrayOfArrays<T> &&other) noexcept {
    arrays_ = other.arrays_;
    width_ = other.width_;
    height_ = other.height_;

    other.arrays_ = nullptr;
    other.width_ = 0;
    other.height_ = 0;
  }
  DynamicArrayOfArrays<T> &operator=(DynamicArrayOfArrays<T> &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }

    FreeBackingArrays();

    arrays_ = rhs.arrays_;
    width_ = rhs.width_;
    height_ = rhs.height_;

    rhs.arrays_ = nullptr;
    rhs.width_ = 0;
    rhs.height_ = 0;

    return *this;
  }

  [[nodiscard]] size_t height() const { return height_; }
  [[nodiscard]] size_t width() const { return width_; }

  T &operator[](size_t i, size_t j) { return At(i, j); }
  const T &operator[](size_t i, size_t j) const { return At(i, j); }

  T &At(size_t i, size_t j) { return arrays_[i][j]; }
  const T &At(size_t i, size_t j) const { return arrays_[i][j]; }

  // Works efficiently thanks to internal representation.
  void SwapRows(size_t indexFrom, size_t indexTo) {
    T *tmp = arrays_[indexTo];
    arrays_[indexTo] = arrays_[indexFrom];
    arrays_[indexFrom] = tmp;
  }

 private:
  T **arrays_;
  size_t height_;
  size_t width_;

  void FreeBackingArrays() {
    for (size_t i = 0; i < height_; ++i) {
      delete[] arrays_[i];
    }
    delete[] arrays_;
  }
};

// It is expected, that the rows are extended by one index to store their maximum at the item [0]. Thus, row indexing is done from 1!
void PopulateMaxInRows(DynamicArrayOfArrays<double> &matrix);

// It is expected, that the rows are extended by one index to store their maximum at the item [0]. Thus, row indexing is done from 1!
void SortByMaxInRow(DynamicArrayOfArrays<double> &matrix);

ctoast::CinResult<DynamicArrayOfArrays<double>> ReadDynamicArray();
}  // namespace app

#endif  // LR4_TASK_3_APP_H_