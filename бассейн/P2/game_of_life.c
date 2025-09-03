#include <stdio.h>
#include <stdlib.h>

#define len 80
#define wer 25

void sortoftwo(int data[]);
void my_time(int sek);
void swap(int *a, int *b);
void input(int **a);
void videl(int ***a);
void output(int **pole, int **life);
int life_yes(int **life);  // есть живые и нет циклов
int **new_life(int **life);
void free_all(int **a);
void end_game();
void fastsort(int *data, int n);
int start_menu();
void rules();
void speedInstructions();

int main(int argc, int *argv[]) {
    int **pole = NULL;
    int **life = NULL;
    start_menu();
    videl(&pole);
    videl(&life);
    input(life);
    int sek = *argv[1] / 709700;  // kostil *-*
    // printf("%d", sek);
    output(pole, life);
    while (life_yes(life)) {
        printf("\033[2J");
        output(pole, life);

        life = new_life(life);
        my_time(sek);
    }
    end_game();
    free_all(pole);
    free_all(life);
    return 0;
}
void videl(int ***a) {
    *a = (int **)calloc(wer, sizeof(int *));
    for (int i = 0; i < wer; i++) {
        (*a)[i] = (int *)calloc(len, sizeof(int));
    }
}

void input(int **life) {
    for (int i = 0; i < wer; i++) {
        for (int j = 0; j < len; j++) {
            scanf("%d", &life[i][j]);
        }
    }
}
void output(int **pole, int **life) {
    for (int j = -1; j <= len; j++) {
        if (j == -1 || j == len) {
            printf("+");
        } else {
            printf("-");
        }
    }
    printf("\n");

    for (int i = 0; i < wer; i++) {
        printf("|");
        for (int j = 0; j < len; j++) {
            if (life[i][j] == 0) {
                printf(" ");  // Мёртвые клетки
            } else {
                printf("@");  // Живые клетки
            }
        }
        printf("|\n");
    }

    for (int j = -1; j <= len; j++) {
        if (j == -1 || j == len) {
            printf("+");
        } else {
            printf("-");
        }
    }
    printf("\n");
}

int life_yes(int **life) {
    int sum = 0;
    for (int i = 0; i < wer; i++) {
        for (int j = 0; j < len; j++) {
            sum += life[i][j];
        }
    }
    return sum;
}

int **new_life(int **life) {
    int **new_state;
    videl(&new_state);
    for (int i = 0; i < wer; i++) {
        new_state[i] = (int *)calloc(len, sizeof(int));
    }
    for (int i = 0; i < wer; i++) {
        for (int j = 0; j < len; j++) {
            int sosid = life[(i - 1 + wer) % wer][(j - 1 + len) % len] + life[(i - 1 + wer) % wer][j] +
                        life[(i - 1 + wer) % wer][(j + 1) % len] + life[i][(j - 1 + len) % len] +
                        life[i][(j + 1) % len] + life[(i + 1) % wer][(j - 1 + len) % len] +
                        life[(i + 1) % wer][j] + life[(i + 1) % wer][(j + 1) % len];

            if (life[i][j] == 1 && (sosid < 2 || sosid > 3)) {
                new_state[i][j] = 0;
            } else if (life[i][j] == 0 && sosid == 3) {
                new_state[i][j] = 1;
            } else {
                new_state[i][j] = life[i][j];
            }
        }
    }
    free_all(life);
    return new_state;
}
void free_all(int **a) {
    for (int i = 0; i < wer; i++) {
        free(a[i]);
    }
    free(a);
}
void end_game() {
    printf("\033[2J");
    printf("Выход? Выход из игры? А я бы еще поиграл.. Возвращайся снова.....иначе тьма поглотит тебя....\n");
}
void my_time(int sek) {
    sek *= 100;
    int second = 10000;
    second += sek;
    second %= 15000;
    int *a = (int *)malloc(second * sizeof(int));
    fastsort(a, second);
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void fastsort(int *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                swap(&data[j], &data[j + 1]);
            }
        }
    }
}

int start_menu() {
    printf("\033[2J");
    printf(
        "===============Привет, друг! Уверен, ты все еще играешь в Понг, но я приготовил еще одну "
        "интересную игру для тебя! ===============\n");
    printf(
        "===============Какой я не гостеприимный, брр...брооу, Ты, наверное, голоден? "
        "=============================\n");
    printf(
        "===============Да, помню, ты говорил, что изголодался по приключениям! Тогда предлагаю "
        "взглянуть на меню и выбрать то, что по вкусу. ============\n");
    printf("=================================== Меню игры 'Жизнь' ===================================\n");
    my_time(500);
    rules();
    speedInstructions();
    printf("\033[2J");
    printf("Всем игрокам приготовиться, начинаем!\n");
    my_time(40);

    return 1;
}
void rules() {
    printf("\033[2J");
    printf("\n=== Правила игры 'Жизнь' ===\n");
    printf(
        "1. Игровое поле представляет собой сетку клеток, каждая из которых может быть живой или мертвой.\n");
    printf("2. На каждом шаге игры состояние клеток изменяется в зависимости от следующих правил:\n");
    printf("   - Живая клетка с менее чем двумя живыми соседями умирает от одиночества.\n");
    printf("   - Живая клетка с двумя или тремя живыми соседями выживает.\n");
    printf("   - Живая клетка с более чем тремя живыми соседями умирает от перенаселения.\n");
    printf("   - Мертвая клетка с ровно тремя живыми соседями оживает.\n");
    my_time(500);
    return;
}
void speedInstructions() {
    printf("\033[2J");
    printf("\n=== Игровые режимы ===\n");
    printf("Чтобы сделать 'Жизнь' медленнее или быстрее, нажимай цифры во время игры:\n");
    printf("Цифра 1. Медленная скорость\n");
    printf("Цифра 2. Средняя скорость\n");
    printf("Цифра 3. Быстрая скорость\n");
    my_time(500);
    return;
}