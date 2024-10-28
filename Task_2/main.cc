#include <expected>
#include "app.h"
#include "ctoast/array.h"
#include "ctoast/control.h"
#include "ctoast/io.h"

using ctoast::CinResult, ctoast::Context, ctoast::Usage;

CinResult<void> Run(Context &);

int main() {
  ctoast::PrintMenu(
      {.Description = "Вводит одномерный статический массив из 10 чисел.",
       .TaskName = "1",
       .TaskOption = std::nullopt,
       .Usages = {
           Usage('r', "Запуск", Run),
           Usage('q', "Выход", [](Context &ctx) -> void { ctx.Exit(); }),
       }});

  return 0;
}

const int kSize = 5;

CinResult<void> Run(Context &_) {
  int kBackingArray[kSize] = {};
  std::cout << "Введите массив из " << kSize << " чисел (через <Enter>):\n";
  auto array = ctoast::StaticArray(kBackingArray);

  return ctoast::ReadArray(array)
      .transform_error([](std::string err) {
        ctoast::PrintError(err);
        return err;
      })
      .and_then([&array]() {
        if (app::IsSortedDescending(array)) {
          std::cout << "Массив отсортирован.\n";
        } else {
          std::cout << "Массив хаотичен.\n";
        }

        return CinResult<void>();
      });
}