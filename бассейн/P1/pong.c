//  сppcheck --enable=all --suppress=missingIncludeSystem pong.c   // Проверка
//  на память gcc -Wall -Werror -Wextra pong.c  // компилируем так clang-format
//  -n  pong.c    - Стилевые тесты - вывод (рядом положить  .clang-format)
//  clang-format -i  pong.c Стилевые тесты - автоисправление (рядом положить
//  .clang-format)

#include <stdio.h>

#define border_x 80
#define border_y 25

int abs(int a) {
  if (a < 0) {
    a *= (-1);
  }
  return a;
}
// int logik_

int main() {
  int points_right = 0;
  int points_left = 0;
  // int rez_pointov = 1;
  int y_need_work; // if 0 ---> |....|  && else ---> ====
  int cen_rocet_l = border_y / 2, cen_rocet_r = border_y / 2;
  int bol_pos_x = border_x / 2, bol_pos_y = border_y / 2;
  int rocet_left = 0, rocet_right = 0;

  int faction = -1; //
  int naprav = 1; // для проверки функции, если при уд,,,,

  while (1) {
    if (points_left > points_right)
      naprav = -1;
    else
      naprav = 1;
    printf("\033[2J");
    for (int y = 1; y <= border_y; y++) {
      if (y == 1 || y == border_y) {
        y_need_work = 1;
      } else {
        y_need_work = 0;
      }
      for (int x = 1; x <= border_x; x++) { // feet at the net

        // viden bol and rocet
        if (bol_pos_x == x && bol_pos_y == y) {
          printf("*");
          continue;
        }

        if (abs(cen_rocet_l - y) <= 1 && x == 2) {
          printf("|");
          continue;
        }
        if (abs(cen_rocet_r - y) <= 1 && x == border_x - 2) {
          printf("|");
          continue;
        }
        if (border_x / 2 - 3 == x && y == 3) {
          printf("%d", points_left);
          continue;
        }
        if (border_x / 2 + 3 == x && y == 3) {
          printf("%d", points_right);
          continue;
        }
        // no smisl
        if (x == border_x / 2 + 1 && y == 1) {
          printf("\\");
          continue;
        }
        if (x == border_x / 2 + 1 && y == border_y) {
          printf("/");
          continue;
        }
        if (y_need_work) {
          if (x == 1)
            printf("*");
          else
            printf("-");
        } else {
          if (x == 1 || x == border_x)
            printf("|");
          // centre
          if (x == border_x / 2)
            printf("|");
          else
            printf(" ");
        }
      }
      // its for beautiful
      if (y_need_work) {
        printf("*");
      }
      // переход делаем в любом случае
      printf("\n");
    }
    // for vvod
    char v;
    v = getchar();
    switch (v) {
    case 'a':
      rocet_left = -1;
      break;
    case 'z':
      rocet_left = 1;
      break;
    case 'k':
      rocet_right = -1;
      break;
    case 'm':
      rocet_right = 1;
      break;
    case ' ':
      rocet_left = 0;
      rocet_right = 0;
      break;
    case 'q':
      points_left = 22;
      points_right = 22;
      break;
    }
    // logig
    // for rocet
    if (cen_rocet_r < border_y - 2 && rocet_right == 1) {
      cen_rocet_r += 1;
    }
    if (cen_rocet_r > 3 && rocet_right == -1) {
      cen_rocet_r -= 1;
    }
    if (cen_rocet_l < border_y - 2 && rocet_left == 1) {
      cen_rocet_l += 1;
    }
    if (cen_rocet_l > 3 && rocet_left == -1) {
      cen_rocet_l -= 1;
    }
    // for bol
    if (bol_pos_x == 1) {
      points_right++;
      bol_pos_x = border_x / 2;
      bol_pos_y = border_y / 2;
    }
    if (bol_pos_x == border_x) {
      points_left++;
      bol_pos_x = border_x / 2;
      bol_pos_y = border_y / 2;
    } else {
      // изменение параметров функции
      if (bol_pos_x == 3 && abs(bol_pos_y - cen_rocet_l) == 1) {
        naprav = 1;
      }
      if (bol_pos_x == border_x - 2 && abs(bol_pos_y - cen_rocet_r) == 1) {
        naprav = -1;
      }
      if (bol_pos_x == 3 && abs(bol_pos_y - cen_rocet_l) == 0) {
        naprav = 0;
      }
      if (bol_pos_y == 1 || bol_pos_y == border_y) {
        faction *= (-1);
      }

      // само вычисление следующей позиции
      if (naprav == 0) {
        bol_pos_x += faction;
      }
      if (faction == -1) {
        if (naprav == -1) {
          bol_pos_y += 1;
          bol_pos_x -= 1;
        } else {
          bol_pos_y -= 1;
          bol_pos_x += 1;
        }
      } else {
        if (naprav == 1) {
          bol_pos_x += 1;
          bol_pos_y += 1;
        } else {
          bol_pos_x -= 1;
          bol_pos_y -= 1;
        }
      }
      // printf("\033[2J");
    }
    if (points_left == 21 || points_right == 21) {
      break;
    }
  }
  if (points_left == points_right) {
    printf("It's Strange");
  }
  if (points_left > points_right) {
    printf("Leht player Win!");
  }
  if (points_left < points_right) {
    printf("Right player Win!");
  }

  return 0;
}
// void logik_rocet()
//