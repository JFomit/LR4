#include "app.h"
#include <cstddef>
#include <expected>
#include <iomanip>
#include "ctoast/io.h"

namespace app {
void PopulateMaxInRows(DynamicArrayOfArrays<double> &matrix) {
  for (size_t j = 0; j < matrix.height(); ++j) {
    double &maxSoFar = matrix[j, 0];
    maxSoFar = matrix[j, 1];
    for (size_t i = 2; i < matrix.width(); ++i) {
      double current = matrix[j, i];
      maxSoFar = current > maxSoFar ? current : maxSoFar;
    }
  }
}

void SortByMaxInRow(DynamicArrayOfArrays<double> &matrix) {
  // a simple O(n^2) bubble sort :D
  size_t height = matrix.height();
  for (size_t i = 0; i < height; ++i) {
    for (size_t j = 0; j < height; ++j) {
      if (matrix[i, 0] < matrix[j, 0]) {
        matrix.SwapRows(i, j);
      }
    }
  }
}

ctoast::CinResult<DynamicArrayOfArrays<double>> ReadDynamicArray() {
  ctoast::PrintLine("Введите M");
  auto resultM = ctoast::Read<size_t>();
  if (!resultM.has_value()) {
    return std::unexpected(resultM.error());
  }
  ctoast::PrintLine("Введите N");
  auto resultN = ctoast::Read<size_t>();
  if (!resultN.has_value()) {
    return std::unexpected(resultN.error());
  }
  std::cout << "Введите матрицу (через <Enter>, всего "
            << resultM.value() * resultN.value() << "):\n";
  auto matrix = DynamicArrayOfArrays(resultM.value() + 1, resultN.value(), 0.0);
  for (size_t j = 0; j < matrix.height(); ++j) {
    matrix[j, 0] = -42;

    for (size_t i = 1; i < matrix.width(); ++i) {
      auto result = ctoast::Read<double>();
      if (result.has_value()) {
        matrix[j, i] = result.value();
      } else {
        return std::unexpected(result.error());
      }
    }
  }

  PopulateMaxInRows(matrix);
  SortByMaxInRow(matrix);

  return matrix;
}
}  // namespace app