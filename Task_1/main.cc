#include <expected>
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

CinResult<void> Run(Context &_) {

  return {};
}