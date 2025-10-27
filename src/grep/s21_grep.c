#include "s21_grep.h"

int main(int argc, char* argv[]) {
  char* optstring = "e:ivcln";
  Flags flags = {0};
  char finding_patterns[4096] = {0};

  read_flags(optstring, argc, argv, finding_patterns, &flags);
  if (!not_flags(&flags)) {
    write_all(argc, argv, finding_patterns, &flags);
  }

  return 0;
}
