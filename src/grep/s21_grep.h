#ifndef S21_GREP_H
#define S21_GREP_H

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  // int h;
  // int s;
  // int f;
  // int o;
} Flags;
int not_flags(Flags* f);
void read_flags(char* optstring, int argc, char** argv, char* finding_patterns,
                Flags* flags);
void write_all(int argc, char** argv, char* finding_patterns, Flags* flags);

#endif