#include "app.h"
#include "ctoast/array2d.h"
#include "gtest/gtest.h"

using ctoast::StaticArray2d;

TEST(task_2, twobytwo) {
  // Arrange
  int mat[2][2] = {{1, 1}, {4, 4}};
  auto matrix = StaticArray2d(mat);
  // Act
  unsigned long product =
      app::GetProductOfPositiveElementsLowerThanMainDiagonal(matrix);
  // Assert
  ASSERT_EQ(product, 4);
}

TEST(task_2, single) {
  // Arrange
  auto matrix = StaticArray2d({{6}});
  // Act
  auto product = app::GetProductOfPositiveElementsLowerThanMainDiagonal(matrix);
  // Assert
  ASSERT_EQ(product, 1);
}