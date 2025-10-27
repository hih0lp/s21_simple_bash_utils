#ifndef S21_CAT_H
#define S21_CAT_H

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flags {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
} Flags;

void write_e_v(int argc, char **argv);
void parse_flag(int argc, char **argv, Flags *f);
void write_b(int argc, char **argv);
void write_E(int argc, char **argv);
void write_n(int argc, char **argv);
void write_s(int argc, char **argv);
void write_tt(int argc, char **argv);
void write(int argc, char **argv);
void write_T(int argc, char **argv);

extern struct option options[];

#endif