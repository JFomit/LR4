#include "app.h"
#include "gtest/gtest.h"

TEST(task_3, single) {
  using namespace app;
  // Arrange
  auto matrix = DynamicArrayOfArrays(2, 1, 0.0);
  // Act
  PopulateMaxInRows(matrix);
  SortByMaxInRow(matrix);
  double value = matrix[0, 1];
  // Assert
  ASSERT_EQ(value, 0.0);
}

TEST(task_3, twobytwo) {
  using namespace app;
  // Arrange
  auto matrix = DynamicArrayOfArrays(3, 2, 0.0);
  matrix[0, 1] = 1.0;
  matrix[0, 2] = 1000.0;
  matrix[1, 1] = 999.0;
  matrix[1, 2] = -10;
  // Act
  PopulateMaxInRows(matrix);
  SortByMaxInRow(matrix);
  double value = 0.0;
  // Assert
  value = matrix[0, 1];
  ASSERT_EQ(value, 999.0);
  value = matrix[0, 2];
  ASSERT_EQ(value, -10);

  value = matrix[1, 1];
  ASSERT_EQ(value, 1.0);
  value = matrix[1, 2];
  ASSERT_EQ(value, 1000.0);
}