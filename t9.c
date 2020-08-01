#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

const char* help =
  "USAGE:\n"
  "    t9 [OPTIONS] [INPUT]\n\n"
  "OPTIONS:\n"
  "    -i         List entries with their index\n"
  "    -d         Verify results in wordlist </usr/share/dict/words>\n"
  "    -df        Same as -d but match full word\n"
  "    -w <path>  Enable dictionary verification with custom wordlist\n"
  "    -e <n>     Select the n'th entry in the return list\n"
  "    -h         Prints help information\n";

const char* dict[10] = {
  " 0",
  "1",      "ABC2",   "DEF3",
  "GHI4",   "JKL5",   "MNO6",
  "PQRS7",  "TUV8",   "WXYZ9"
};

FILE* fp = NULL;
size_t len = 0;

uint64_t
  entry,
  iter;

bool
  match_full,
  dict_on,
  show_entry,
  select_entry;

char
  *line = NULL,
  *dict_path = "/usr/share/dict/words";

void print_entry(char* string) {
  if (!(entry != ++iter && select_entry)) {
    show_entry
      ? printf("%llu:\t%s\n", iter, string)
      : printf("%s\n", string);

    if (select_entry) {
      exit(0);
    }
  }
}

char* strtoupper(char* string) {
  uint64_t i = 0;
  size_t len = strlen(string);
  char* out = malloc(len * sizeof(char));
  out[len] = '\0';

  while (string[i]) {
    out[i] = toupper(string[i]);
    i++;
  }

  return out;
}

void check_dict(char* string) {
  fseek(fp, 0, SEEK_SET);

  while (getline(&line, &len, fp) != -1) {
    line[strcspn(line, "\n")] = 0;

    if (match_full) {
      if (!strcmp(strtoupper(line), string)) { print_entry(line); }
    } else {
      if (strstr(strtoupper(line), string)) { print_entry(line); }
    }
  }
}

void t9_apply(char array[], uint64_t pos, char* input) {
  const char* set = dict[(uint8_t)input[pos] - 48];

  for (uint64_t i = 0; i < strlen(set); i++) {
    array[pos] = set[i];

    if (pos == strlen(array) - 1) {
      dict_on
        ? check_dict(array)
        : print_entry(array);
    } else {
      t9_apply(array, pos + 1, input);
    }
  }
}

char* clean_string(char* in) {
  char* out = malloc(sizeof(char) * strlen(in) + 1);

  uint64_t i, v = 0;

  for (i = 0; i <= strlen(in); i++) {
    if (in[i] < 0 || in[i] > '9') { continue; }
    out[v++] = in[i];
    if (in[i + 1] == '\0') { out[v] = '\0'; }
  }

  free(in);
  return out;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    puts(help);
    return 0;
  }

  uint64_t i, v = 0, size = argc - 1;
  char* str = (char*)malloc(v);

  for (i = 1; i <= size; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
        case 'd': {
          if (argv[i][2] == 'f') { match_full = true; }
          dict_on = true;
          continue;
        } case 'e': {
          select_entry = true;
          entry = (uint64_t)atoi(argv[++i]);
          continue;
        } case 'w': {
          dict_path = argv[++i];
          dict_on = true;
          continue;
        } case 'i': {
          show_entry = true;
          continue;
        } case 'h': {
          puts(help);
          exit(0);
        }
      }
    } else {
      str = (char*)realloc(str, (v + strlen(argv[i])));
      strcat(str, argv[i]);
    }
  }

  if (dict_on) {
    fp = fopen(dict_path, "r");

    if (!fp) {
      fprintf(stderr, "t9: error: failed to open dictionary: %s\n", dict_path);
      exit(1);
    }
  }

  char* input = clean_string(str);

  if (strlen(input) < 1) {
    fprintf(stderr, "t9: error: input string empty.");
    exit(1);
  }

  size_t len = strlen(input) + 1;
  char bus[len];
  memset(bus, ' ', len);
  bus[len - 1] = '\0';

  t9_apply(bus, 0, input);

  if (dict_on) { fclose(fp); }

  return 0;
}
