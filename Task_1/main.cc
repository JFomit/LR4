#include "app.h"
#include "ctoast/control.h"

using ctoast::Context, ctoast::Usage;

int main() {
  ctoast::PrintMenu(
      {.Description = "Вводит одномерный статический массив из 10 чисел.",
       .TaskName = "1",
       .TaskOption = std::nullopt,
       .Usages = {Usage('q', "Выход", [](Context &ctx) -> void { ctx.Exit(); }),
                  Usage('r', "Ввести и вычислить", DoMain)}});

  return 0;
}
