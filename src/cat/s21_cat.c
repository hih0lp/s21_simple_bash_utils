#include "s21_cat.h"

int main(int argc, char **argv) {
  Flags f = {0};
  parse_flag(argc, argv, &f);

  if (f.b)
    write_b(argc, argv);
  else if (f.e)
    write_e_v(argc, argv);
  else if (f.E)
    write_E(argc, argv);
  else if (f.n)
    write_n(argc, argv);
  else if (f.s)
    write_s(argc, argv);
  else if (f.t)
    write_tt(argc, argv);
  else if (f.T)
    write_T(argc, argv);
  else
    write(argc, argv);

  return 0;
}
