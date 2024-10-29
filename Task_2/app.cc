#include "app.h"
#include <algorithm>
#include <cstddef>

namespace app {
unsigned long GetProductOfPositiveElementsLowerThanMainDiagonal(
    const ctoast::Array2d<int> &matrix) {
  size_t min = std::min(matrix.width(), matrix.height());

  unsigned long productSoFar = 1;
  for (size_t j = 0; j < min; ++j) {
    for (size_t i = 0; i < j; ++i) {
      int current = matrix[j, i];
      productSoFar *= current > 0 ? (unsigned long)current : 1;
    }
  }

  return productSoFar;
}
}  // namespace app