#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char a = 'a';
const char z = 'z';
const char dot = '.';

typedef struct WORD {
  int position;
  int length;
  int found;
  char * line;
}
word;

int compare(const void * a,
  const void * b) {
  word * word_a = (word * ) a;
  word * word_b = (word * ) b;
  return strcmp(word_a->line, word_b->line);
}

void find_word(int x, int y, int * resulting_indexes, int add_x, int add_y, word * word, char ** riddle, int max_x);
int main() {
  char temp_char;
  printf("Zadejte osmismerku:\n");

  int max_x = 10;
  int x = 0;
  char * first_line = (char * ) malloc(max_x * sizeof( * first_line));
  if (first_line == NULL) {
    return 1;
  }
  while (1) {
    int scan_result = scanf("%c", & temp_char);
    if (temp_char == '\n' && scan_result != EOF) {
      break;
    }
    if (x == max_x) {
      max_x *= 2;
      first_line = (char * ) realloc(first_line, max_x * sizeof( * first_line));
      if (first_line == NULL) {
        int temp = max_x / 4;
        while (first_line == NULL) {
          first_line = (char * ) realloc(first_line, (max_x + temp) * sizeof( * first_line));
          if (temp >= max_x / 2) {
            return 1;
          }
        }
        max_x = temp;
      }
    }
    if (!(temp_char == dot || (a <= temp_char && temp_char <= z)) || scan_result == EOF) {
      printf("Nespravny vstup.\n");
      free(first_line);
      return 1;
    }
    first_line[x] = temp_char;
    x++;
  }
  int y = 1;
  int max_y = x > 5 ? (x + 1) : 5;
  char ** riddle = (char ** ) malloc(max_y * sizeof( * riddle));
  if (riddle == NULL) {
    int temp = max_y / 2;
    while (riddle == NULL) {
      riddle = (char ** ) malloc(temp * sizeof( * riddle));
      temp /= 2;
      if (temp == 1) {
        return 1;
      }
    }
    max_y = temp;
  }
  riddle[0] = first_line;
  while (1) {
    riddle[y] = (char * ) malloc(x * sizeof( * (riddle[y])));
    if (riddle[y] == NULL) {
      return 1;
    }
    int i = 0;
    while (1) {
      int scan_result = scanf("%c", & temp_char);
      if (temp_char == '\n' && scan_result != EOF) {
        break;
      }
      if (!(temp_char == dot || (a <= temp_char && temp_char <= z)) || scan_result == EOF) {
        printf("Nespravny vstup.\n");
        for (int i = 0; i < y; i++) {
          free(riddle[i]);
        }
        free(riddle);
        return 1;
      }
      riddle[y][i] = temp_char;
      i++;
      if (i > x) {
        printf("Nespravny vstup.\n");
        for (int i = 0; i < y; i++) {
          free(riddle[i]);
        }
        free(riddle);
        return 1;
      }
    }
    if (i == 0) {
      free(riddle[y]);
      break;
    }
    if (i != x) {
      printf("Nespravny vstup.\n");
      free(riddle);
      return 1;
    }
    y++;
    if (y == max_y) {
      max_y *= 2;
      riddle = (char ** ) realloc(riddle, max_y * (sizeof( * riddle)));
      if (riddle == NULL) {
        int temp = max_y / 4;
        while (riddle == NULL) {
          riddle = (char ** ) realloc(riddle, (max_y + temp) * (sizeof( * riddle)));
          if (temp >= max_y) {
            return 1;
          }
        }
        max_y = temp;
      }
    }
  }

  int word_count = 0;
  int max_words = 10;
  word * words = (word * ) malloc(max_words * sizeof( * words));
  if (words == NULL) {
    int tmp = max_words / 2;
    while (words == NULL) {
      words = (word * ) malloc(tmp * sizeof( * words));
      if (tmp == 1) {
        return 1;
      }
      tmp /= 2;
    }
    max_words = tmp;
  }
  while (1) {
    if (scanf("%c", & temp_char) == EOF) {
      break;
    }
    int max_word_length = 10;
    word * init_word = (word * ) malloc(sizeof(word));
    if (init_word == NULL) {
      return 1;
    }
    init_word->position = word_count;
    init_word->line = (char * ) malloc(max_word_length * sizeof(char * ));
    if (init_word->line == NULL) {
      int tmp = max_word_length / 2;
      while (init_word->line == NULL) {
        init_word->line = (char * ) malloc(tmp * sizeof(char * ));
        if (tmp == 1) {
          return 1;
        }
        tmp /= 2;
      }
      max_word_length = tmp;
    }
    init_word->line[0] = temp_char;
    init_word->found = 0;
    int length = 1;
    while (1) {
      int scan_result = scanf("%c", & temp_char);
      if (temp_char == '\n') {
        break;
      }
      if (temp_char < a || z < temp_char || scan_result == EOF) {
        printf("Nespravny vstup.\n");
        for (int i = 0; i < word_count; i++) {
          free(words[i].line);
        }
        free(words);
        for (int i = 0; i < y; i++) {
          free(riddle[i]);
        }
        free(riddle);
        return 1;
      }
      init_word->line[length] = temp_char;
      length++;
      if (length == max_word_length) {
        max_word_length *= 2;
        init_word->line = (char * ) realloc(init_word->line, max_word_length * sizeof(char * ));
        if (init_word->line == NULL) {
          int tmp = max_word_length / 4;
          while (init_word->line == NULL) {
            init_word->line = (char * ) realloc(init_word->line, (max_word_length + tmp) * sizeof(char * ));
            if (tmp >= max_word_length / 2) {
              return 1;
            }
            tmp /= 2;
          }
          max_word_length = tmp;
        }
      }
    }
    init_word->length = length;
    words[word_count] = * init_word;
    word_count++;
    if (word_count == max_words) {
      max_words *= 2;
      words = (word * ) realloc(words, max_words * (sizeof( * words)));
      if (words == NULL) {
        int tmp = max_words / 4;
        while (words == NULL) {
          words = (word * ) realloc(words, (max_words / 2 + tmp) * (sizeof( * words)));
          if (tmp >= max_words / 2) {
            return 1;
          }
          tmp /= 2;
        }
      }
    }
    free(init_word);
  }

  qsort(words, word_count, sizeof(word), compare);

  int * resulting_indexes = (int * ) malloc(x * y * sizeof( * resulting_indexes));
  if (resulting_indexes == NULL) {
    return 1;
  }

  memset(resulting_indexes, 0, x * y * sizeof(int));
  if (word_count != 0) {
    word * currentlyComparing = NULL;
    for (int i = 0; i < y; i++) {
      for (int k = 0; k < x; k++) {
        currentlyComparing = & words[0];
        int word_index = 0;

        while (currentlyComparing->line[0] <= riddle[i][k]) {
          if (currentlyComparing->line[0] < riddle[i][k]) {
            word_index++;
            if (word_index == word_count) {
              break;
            }
            currentlyComparing = & words[word_index];
            continue;
          }
          int cur_len = currentlyComparing->length - 1;
          int top = i;
          int bottom = y - i;
          int left = k;
          int right = x - k;
          if (right >= cur_len) {
            find_word(k, i, resulting_indexes, 1, 0, currentlyComparing, riddle, x);
            if (bottom >= cur_len) {
              find_word(k, i, resulting_indexes, 1, 1, currentlyComparing, riddle, x);
            }
            if (top >= cur_len) {
              find_word(k, i, resulting_indexes, 1, -1, currentlyComparing, riddle, x);
            }
          }
          if (left >= cur_len) {
            find_word(k, i, resulting_indexes, -1, 0, currentlyComparing, riddle, x);
            if (bottom >= cur_len) {
              find_word(k, i, resulting_indexes, -1, 1, currentlyComparing, riddle, x);
            }
            if (top >= cur_len) {
              find_word(k, i, resulting_indexes, -1, -1, currentlyComparing, riddle, x);
            }
          }
          if (bottom >= cur_len) {
            find_word(k, i, resulting_indexes, 0, 1, currentlyComparing, riddle, x);
          }
          if (top >= cur_len) {
            find_word(k, i, resulting_indexes, 0, -1, currentlyComparing, riddle, x);
          }
          word_index++;
          if (word_index == word_count) {
            break;
          }
          currentlyComparing = & words[word_index];
        }
      }
    }

    word * unused_word = NULL;
    for (int i = 0; i < word_count; i++) {
      if (!words[i].found) {
        if (unused_word == NULL) {
          unused_word = & words[i];
        } else {
          if (unused_word->position > words[i].position) {
            unused_word = & words[i];
          }
        }
      }
    }

    if (unused_word != NULL) {
      printf("Slovo '%s' nenalezeno.\n", unused_word->line);
      for (int i = 0; i < y; i++) {
        free(riddle[i]);
      }
      free(riddle);
      free(resulting_indexes);
      for (int i = 0; i < word_count; i++) {
        free(words[i].line);
      }
      free(words);
      return 0;
    }

    for (int i = 0; i < word_count; i++) {
      free(words[i].line);
    }
    free(words);
    printf("Vysledek:\n");
    int line_length = 0;
    for (int i = 0; i < y; i++) {
      for (int k = 0; k < x; k++) {
        if (line_length == 60) {
          printf("\n");
          line_length = 0;
        }
        if (riddle[i][k] != '.') {
          if (! * (resulting_indexes + i * x + k)) {
            line_length++;
            printf("%c", riddle[i][k]);
          }
        }
      }
    }
    if (line_length != 0) {
      printf("\n");
    }
    free(resulting_indexes);
    for (int i = 0; i < y; i++) {
      free(riddle[i]);
    }
    free(riddle);
    return 0;
  }
}
void find_word(int x, int y, int * resulting_indexes, int add_x, int add_y, word * word, char ** riddle, int max_x) {
  for (int i = 0; i < word->length; i++) {
    if (word->line[i] != riddle[add_y * i + y][add_x * i + x]) {
      return;
    }
  }
  word->found = 1;
  int result_x = x;
  int result_y = y;
  for (int i = 0; i < word->length; i++) {
    *(resulting_indexes + result_y * max_x + result_x) = 1;
    result_x += add_x;
    result_y += add_y;
  }
}
