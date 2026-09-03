#include <cstdlib>
#include <qd/fpu.h>
#include "config.h"

#define f_main FC_FUNC_(f_main, F_MAIN)

#ifdef FC_FUNC
#  undef FC_FUNC
#endif
#ifdef FC_FUNC_
#  undef FC_FUNC_
#endif
#define FC_FUNC(name, NAME)   name##_
#define FC_FUNC_(name, NAME)  name##_

extern "C" void f_main();

int main() {
  fpu_fix_start(NULL);
  f_main();
  return 0;
}

