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

void parse_flag(int argc, char **argv, Flags *f) {
  int res;
  int opt_index = 1;

  while ((res = getopt_long(
              argc, argv, "beEnstT", options,
              &opt_index)) !=  // opt_index позволяет идентифицировать
                               // конкретную длинную опцию
         -1) {
    switch (res) {
      case 'b':
        f->b = 1;
        break;
      case 'e':
        f->e = 1;
        break;
      case 'E':
        f->E = 1;
        break;
      case 'n':
        f->n = 1;
        break;
      case 's':
        f->s = 1;
        break;
      case 't':
        f->t = 1;
        break;
      case 'T':
        f->T = 1;
        break;
      default:
        fprintf(
            stderr,
            "\ncat: illegal option -- %s\nusage: cat [-benstuv] [file ...]\n",
            argv[optind]);
        exit(1);
        break;
    }
  }
}

void write(int argc, char **argv) {
  char buf[4096];

  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
    }
    while (fgets(buf, 4096, f)) {
      printf("%s", buf);
    }
  }
}

void write_b(int argc, char **argv) {
  char buf[4096];
  int line_number = 1;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while (fgets(buf, 4096, f)) {
      if (strcmp("\n", buf) == 0)
        printf("%s", buf);
      else
        printf("%6d\t%s", line_number++, buf);
    }

    // printf("\n");
    fclose(f);
  }
}

void write_e_v(int argc, char **argv) {
  int c;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }

    while ((c = getc(f)) != EOF) {
      if (c == '\n')
        printf("$\n");
      else if (c == '\t')
        printf("\t");  // таб оставляем
      else if (c == 127)
        printf("^?");
      else if (c < 32)
        printf("^%c", c + 64);
      else if (c > 127) {  // высокобитные файлы
        printf("M-");
        if (c - 128 < 32)
          printf("^%c", c - 128 + 64);
        else if (c - 128 == 127)
          printf("^?");
        else
          putchar(c - 128);
      } else
        putchar(c);
    }
    fclose(f);
  }
}

void write_E(int argc, char **argv) {
  int c;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while ((c = getc(f)) != EOF) {
      if (c == '\n')
        printf("$\n");
      else
        putchar(c);
    }
    fclose(f);
  }
}

void write_n(int argc, char **argv) {
  char buf[4096];
  int line_number = 1;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while (fgets(buf, 4096, f)) {
      printf("%6d\t%s", line_number++, buf);
    }
    fclose(f);
  }
}

void write_s(int argc, char **argv) {
  char buf[4096];
  int empty_strings = 0;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while (fgets(buf, 4096, f)) {
      if (strcmp(buf, "\n") == 0) {
        empty_strings++;
      } else if (empty_strings >= 2 && strcmp(buf, "\n") != 0) {
        printf("\n%s", buf);
        empty_strings = 0;
      } else {
        if (empty_strings == 1)
          printf("\n%s", buf);
        else
          printf("%s", buf);
        empty_strings = 0;
      }
    }
    fclose(f);
  }
}

void write_tt(
    int argc,
    char **argv) {  // tt, потому что write_t - это какой-то тип данных
  int c;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }

    while ((c = getc(f)) != EOF) {
      if (c == '\n')
        printf("\n");
      else if (c == '\t')
        printf("^I");  // таб оставляем
      else if (c == 127)
        printf("^?");
      else if (c < 32)
        printf("^%c", c + 64);
      else if (c > 127) {  // высокобитные файлы
        printf("M-");
        if (c - 128 < 32)
          printf("^%c", c - 128 + 64);
        else if (c - 128 == 127)
          printf("^?");
        else
          putchar(c - 128);
      } else
        putchar(c);
    }
    fclose(f);
  }
}

void write_T(int argc, char **argv) {
  int c;
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while ((c = getc(f)) != EOF) {
      if (c == '\t')
        printf("^I");
      else
        putchar(c);
    }
    fclose(f);
  }
}