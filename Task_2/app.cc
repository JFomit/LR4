#include "app.h"

namespace app {
bool IsSortedDescending(const ctoast::Array<int> &array) {
  if (array.size() <= 2) {
    return true;
  }

  bool all_less = true;

  for (size_t i = 1; i < array.size(); ++i) {
    int last = array[i - 1];
    int current = array[i];

    all_less &= current <= last;
  }

  return all_less;
}
}  // namespace app
