#include <cstddef>
#include <iomanip>
#include <optional>
#include "app.h"
#include "ctoast/control.h"
#include "ctoast/io.h"

ctoast::CinResult<void> Run(ctoast::Context &ctx);

int main() {
  ctoast::PrintMenu({.Description = "todo!()",
                     .TaskName = "3",
                     .TaskOption = std::make_optional("4"),
                     .Usages = {ctoast::Usage('r', "Запуск", Run),
                                ctoast::Usage::CreateQuit()}});
}

ctoast::CinResult<void> Run(ctoast::Context &_) {
  return app::ReadDynamicArray().transform([](auto matrix) -> void {
    app::PopulateMaxInRows(matrix);
    app::SortByMaxInRow(matrix);

    ctoast::PrintLine("Отсортированная матрица:");
    for (size_t j = 0; j < matrix.height(); ++j) {
      for (size_t i = 1; i < matrix.width(); ++i) {
        std::cout << std::setw(2) << matrix[j, i] << ' ';
      }
      std::cout << '\n';
    }
  });
}