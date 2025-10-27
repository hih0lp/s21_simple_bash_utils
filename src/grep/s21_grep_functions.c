#include "s21_grep.h"

void read_flags(char* optstring, int argc, char** argv, char* finding_patterns,
                Flags* flags) {
  int count_of_patterns = 0;
  int is_end = 0;
  int res;
  while (
      (res = getopt_long(argc, argv, optstring, NULL, NULL)) != -1 &&
      !is_end) {  // getopt_long - обрабатывает и короткие, и длинные параметры
    switch (res) {
      case 'e':
        flags->e = 1;
        if (count_of_patterns > 0)
          strcat(finding_patterns,
                 "|");  // тупо разделитель, костыль, спасибо челу за подсказку
        count_of_patterns++;
        strcat(finding_patterns, optarg);  // optarg - указатель на элемент
                                           // argv, в котором сейчас находимся
        is_end = 1;
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      default:
        // printf("message about error, hz, che dalshe delat' nado bylo");
        break;
    }
  }
}

int not_flags(Flags* flags) {
  if (!flags->e && !flags->i && !flags->v && !flags->c && !flags->l &&
      !flags->n)
    return 1;
  return 0;
}

void write_all(int argc, char** argv, char* finding_patterns, Flags* flags) {
  regex_t reg;
  int reg_flags = REG_EXTENDED;
  int file_matched = 0;

  if (flags->i) reg_flags |= REG_ICASE;  // проверка на игнор регистра
  if (!flags->e)
    finding_patterns =
        argv[optind++];  // если нет флага -e, то сдвигаем указатель на
                         // следующий индекс для паттерна

  char buf[4096];
  for (int i = optind; i < argc; i++) {
    int match_strings = 0;  // кол-во совпавших строк
    int all_strings = 0;    // каунтер всех строк
    int result;  // просто результат совпадения
    FILE* f = fopen(argv[i], "r");

    if (!f) {
      fprintf(stderr, "failed to open %s\n", argv[i]);  // сообщение об ошибке
      return;
    }  // возможно, нужно будет убрать ретурн
    regcomp(&reg, finding_patterns, reg_flags);  // компиляция регекса

    while (fgets(buf, 4096, f)) {
      all_strings++;  //+1 строка при каждой строке, логично :)
      result = regexec(&reg, buf, 0, NULL, 0);  // поиск в строке по регексу
      int is_match = (result == 0);  // есть ли совпадение или нет

      if (flags->v)
        is_match =
            !is_match;  // инверсия поиска, если не нашло ничего -> ставим нашло

      if (is_match) {  // если ок
        match_strings++;
        file_matched++;  // пройденный файл
        if (flags->l)
          break;  // если флаг l, то брейк, поскольку нужен чисто файл

        if (!flags->c) {  // если нет флага в принципе, то есть обычный вывод
          if (argc - optind > 1)
            printf("%s:",
                   argv[i]);  // если больше 1 флага, то нужно вывести имя файла
          if (flags->n)
            printf("%d:", all_strings);  // если есть, то нужно вывести номер
                                         // строки, где есть совпадение
          printf("%s", buf);  // вывод строки, соответственно
        }
      }
    }
    fclose(f);

    if (flags->l && file_matched)  // если есть флаг и файл пройден
      printf("%s\n", argv[i]);  // вывод файла, где есть совпадение
    else if (flags->c) {  // если есть флаг
      if (argc - optind > 1)
        printf("%s:", argv[i]);  // см коммент на строке
                                 // 111
      printf("%d\n", flags->v ? (all_strings - match_strings)
                              : match_strings);  // вывод (не)совпадающих
    }
  }
}