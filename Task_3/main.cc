#include <cstddef>
#include <iomanip>
#include <optional>
#include "app.h"
#include "ctoast/array2d.h"
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
  return {};
}