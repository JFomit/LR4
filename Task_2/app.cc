#include "app.h"

namespace app {
bool IsSorted(const ctoast::Array<int> &array) {
  if (array.size() <= 2) {
    return true;
  }

  bool all_less = true;
  bool all_greater = true;
  bool all_equal = true;

  for (size_t i = 1; i < array.size(); ++i) {
    int last = array[i - 1];
    int current = array[i];

    all_less &= current <= last;
    all_greater &= current >= last;
    all_equal &= current == last;
  }

  return all_equal | (all_less ^ all_greater);
}
}  // namespace app
