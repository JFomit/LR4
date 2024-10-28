#include "app.h"
#include "ctoast/array.h"
#include "gtest/gtest.h"

using ctoast::StaticArray;

TEST(app_tests, small_array) {
  // Arrange
  int data1[] = {0, 1};
  int data2[] = {42, -519};
  int data3[] = {42};
  // int data4[] = {};
  auto array1 = StaticArray(data1);
  auto array2 = StaticArray(data2);
  auto array3 = StaticArray(data3);
  // auto array4 = StaticArray<int, 0>(data4);
  // Act
  bool is_sorted1 = app::IsSorted(array1);
  bool is_sorted2 = app::IsSorted(array2);
  bool is_sorted3 = app::IsSorted(array3);
  // bool is_sorted4 = app::IsSorted(array4);
  // Assert
  ASSERT_TRUE(is_sorted1);
  ASSERT_TRUE(is_sorted2);
  ASSERT_TRUE(is_sorted3);
  // ASSERT_TRUE(is_sorted4);
}

TEST(app_tests, sorted_array_less) {
  // Arrange
  int data[] = {0, 1, 2, 3, 4, 5, 6};
  auto array = StaticArray(data);
  // Act
  bool is_sorted = app::IsSorted(array);
  // Assert
  ASSERT_TRUE(is_sorted);
}

TEST(app_tests, sorted_array_greater) {
  // Arrange
  int data[] = {3, 2, 1};
  auto array = StaticArray(data);
  // Act
  bool is_sorted = app::IsSorted(array);
  // Assert
  ASSERT_TRUE(is_sorted);
}

TEST(app_tests, same_array) {
  // Arrange
  int data[] = {0, 0, 0, 0, 0, 0};
  auto array = StaticArray(data);
  // Act
  bool is_ordered = app::IsSorted(array);
  // Assert
  ASSERT_TRUE(is_ordered);
}

TEST(app_tests, simple_unsorted_array) {
  // Arrange
  int data[] = {3, 1, 2};
  auto array = StaticArray(data);
  // Act
  bool is_ordered = app::IsSorted(array);
  // Assert
  ASSERT_FALSE(is_ordered);
}

TEST(app_tests, bigger_unsorted_array) {
  // Arrange
  int data[] = {3, 1, 2, -5, -5, -6, -7};
  auto array = StaticArray(data);
  // Act
  bool is_ordered = app::IsSorted(array);
  // Assert
  ASSERT_FALSE(is_ordered);
}

TEST(app_tests, unsorted_array_one) {
  // Arrange
  int data1[] = {0, 0, 0, 1};
  int data2[] = {0, 0, 0, -1};
  auto array1 = StaticArray(data1);
  auto array2 = StaticArray(data2);
  // Act
  bool is_ordered1 = app::IsSorted(array1);
  bool is_ordered2 = app::IsSorted(array2);
  // Assert
  ASSERT_TRUE(is_ordered1);
  ASSERT_TRUE(is_ordered2);
}
