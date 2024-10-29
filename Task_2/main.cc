#include <cstddef>
#include <iomanip>
#include <optional>
#include "app.h"
#include "ctoast/array2d.h"
#include "ctoast/control.h"
#include "ctoast/io.h"

ctoast::CinResult<void> Run(ctoast::Context &ctx);

int main() {
  ctoast::PrintMenu(
      {.Description =
           "Вычисляет произведение положительных элементов матрицы (хардкод), "
           "расположенных ниже главной диагонали.",
       .TaskName = "2",
       .TaskOption = std::make_optional("4"),
       .Usages = {ctoast::Usage('r', "Запуск", Run),
                  ctoast::Usage::CreateQuit()}});
}

const int kBackingMatrix[4][3] = {{1, 2, 3},
                                  {5, 6, 7},
                                  {9, 10, 11},
                                  {12, 13, 14}};
ctoast::CinResult<void> Run(ctoast::Context &_) {
  auto matrix = ctoast::StaticArray2d(kBackingMatrix);

  std::cout << "Исходные данные:\n";

  for (size_t i = 0; i < matrix.width(); ++i) {
    for (size_t j = 0; j < matrix.height(); ++j) {
      std::cout << std::setw(2) << std::setfill(' ') << matrix[i, j] << ' ';
    }
    std::cout << '\n';
  }

  std::cout << "Искомое произведение: "
            << app::GetProductOfPositiveElementsLowerThanMainDiagonal(matrix)
            << '\n';

  return {};
}