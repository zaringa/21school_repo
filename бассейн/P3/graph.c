#include "graph.h"

int main() {
    char exp[100];
    printf("Your equation\n");
    fgets(exp, sizeof(exp), stdin);
    exp[strcspn(exp, "\n")] = '\0';
    Token *inf_tok = NULL;
    int num_inf_tok = 0;
    paex(exp, &inf_tok, &num_inf_tok);

    Token *ps_tok = NULL;
    int num_ps_tok = 0;
    inf_cur(inf_tok, num_inf_tok, &ps_tok, &num_ps_tok);

    int graphic_matrix[HEIGHT][WIDTH];
    grr(graphic_matrix);
    work_work(graphic_matrix, ps_tok, num_ps_tok);
    print_graph(graphic_matrix);

    free(inf_tok);
    free(ps_tok);
    return 0;
}

void grr(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = '.';
        }
    }
}

void print_graph(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(matrix[i][j]);
        }
        putchar('\n');
    }
}
void work_work(int matrix[HEIGHT][WIDTH], const Token *post_tok, int num_tok) {
    for (int i = 0; i < WIDTH; i++) {
        double x = (i * 4.0 * M_PI) / (WIDTH - 1);
        double res = risov_fan(post_tok, num_tok, x);
        int y = round((res + 1) * (HEIGHT - 1) / 2);
        if (y >= 0 && y < HEIGHT) {
            matrix[y][i] = '*';
        }
    }
}

int precedence(const char *op) {
    int priority = 0;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        priority = 1;
    } else if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        priority = 2;
    } else if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || strcmp(op, "tan") == 0 ||
               strcmp(op, "ctg") == 0 || strcmp(op, "sqrt") == 0 || strcmp(op, "ln") == 0) {
        priority = 2;
    }
    return priority;
}

void num_var(Token **post_tok, int *num_tok, const Token *cur_tok) {
    (*num_tok)++;
    *post_tok = (Token *)realloc(*post_tok, sizeof(Token) * (*num_tok));
    (*post_tok)[(*num_tok) - 1] = *cur_tok;
}

void un_mi_2(const Token *inf_tok, Token **post_tok, int *num_tok, int *i) {
    const Token *next_token = &inf_tok[*i + 1];
    if (next_token->type == LEFT_PAREN && inf_tok[*i + 2].value[0] == '$') {
        *i = *i + 2;
    } else if (next_token->type == LEFT_PAREN &&
               (inf_tok[*i + 2].type == NUMBER || inf_tok[*i + 2].type == VARIABLE)) {
        char new_value[50];
        new_value[0] = '-';
        for (int j = 1; inf_tok[*i + 2].value[j - 1] != '\0'; j++) {
            new_value[j] = inf_tok[*i + 2].value[j - 1];
            if (inf_tok[*i + 2].value[j - 1] == '\0') {
                new_value[j + 1] = '\0';
            }
        }
        (*num_tok)++;
        *post_tok = (Token *)realloc(*post_tok, sizeof(Token) * (*num_tok));
        (*post_tok)[(*num_tok) - 1].type = inf_tok[*i + 2].type;
        strcpy((*post_tok)[(*num_tok) - 1].value, new_value);

        *i = *i + 2;
    } else if (next_token->value[0] == '$') {
        *i = *i + 1;
    }
    if (next_token->type == NUMBER || next_token->type == VARIABLE) {
        char new_value[50];
        new_value[0] = '-';
        for (int j = 1; next_token->value[j - 1] != '\0'; j++) {
            new_value[j] = next_token->value[j - 1];
            if (next_token->value[j - 1] == '\0') {
                new_value[j + 1] = '\0';
            }
        }

        (*num_tok)++;
        *post_tok = (Token *)realloc(*post_tok, sizeof(Token) * (*num_tok));
        (*post_tok)[(*num_tok) - 1].type = next_token->type;
        strcpy((*post_tok)[(*num_tok) - 1].value, new_value);
        *i = *i + 1;
    }
}

void no_min(Stack *op_stek, Token **post_tok, int *num_tok, const Token *cur_tok) {
    while (!stack_empty(op_stek) && precedence(stack_top(op_stek)) >= precedence(cur_tok->value) &&
           strcmp(stack_top(op_stek), "(") != 0) {
        char *op = stack_pop(op_stek);
        (*num_tok)++;
        *post_tok = (Token *)realloc(*post_tok, sizeof(Token) * (*num_tok));
        (*post_tok)[(*num_tok) - 1].type = OPERATOR;
        strcpy((*post_tok)[(*num_tok) - 1].value, op);
        free(op);
    }
    stack_push(op_stek, cur_tok->value);
}

void rt_bb(Stack *op_stek, Token **post_tok, int *num_tok) {
    while (!stack_empty(op_stek) && strcmp(stack_top(op_stek), "(") != 0) {
        char *op = stack_pop(op_stek);
        (*num_tok)++;
        *post_tok = (Token *)realloc(*post_tok, sizeof(Token) * (*num_tok));
        (*post_tok)[(*num_tok) - 1].type = OPERATOR;
        strcpy((*post_tok)[(*num_tok) - 1].value, op);
        free(op);
    }

    char *op = stack_pop(op_stek);
    free(op);
    if (!stack_empty(op_stek) && stack_top(op_stek)[0] != '(') {
        if (strcmp(stack_top(op_stek), "sin") == 0 || strcmp(stack_top(op_stek), "cos") == 0 ||
            strcmp(stack_top(op_stek), "tan") == 0 || strcmp(stack_top(op_stek), "ctg") == 0 ||
            strcmp(stack_top(op_stek), "sqrt") == 0 || strcmp(stack_top(op_stek), "ln") == 0) {
            char *function = stack_pop(op_stek);
            (*num_tok)++;
            *post_tok = (Token *)realloc(*post_tok, sizeof(Token) * (*num_tok));
            (*post_tok)[(*num_tok) - 1].type = FUNCTION;
            strcpy((*post_tok)[(*num_tok) - 1].value, function);
            free(function);
        }
    }
}

void inf_cur(const Token *inf_tok, int num_inf_tok, Token **post_tok, int *num_tok) {
    *num_tok = 0;
    *post_tok = NULL;
    Stack op_stek;
    stack_init(&op_stek, num_inf_tok);
    for (int i = 0; i < num_inf_tok; i++) {
        const Token *cur_tok = &inf_tok[i];
        if (cur_tok->type == NUMBER || cur_tok->type == VARIABLE) {
            num_var(post_tok, num_tok, cur_tok);
        } else if (cur_tok->type == OPERATOR) {
            if (cur_tok->value[0] == '$') {
                un_mi_2(inf_tok, post_tok, num_tok, &i);
            } else {
                no_min(&op_stek, post_tok, num_tok, cur_tok);
            }
        } else if (cur_tok->type == FUNCTION) {
            stack_push(&op_stek, cur_tok->value);
        } else if (cur_tok->type == LEFT_PAREN) {
            stack_push(&op_stek, cur_tok->value);
        } else if (cur_tok->type == RIGHT_PAREN) {
            rt_bb(&op_stek, post_tok, num_tok);
        }
    }
    while (!stack_empty(&op_stek)) {
        char *op = stack_pop(&op_stek);
        (*num_tok)++;
        *post_tok = (Token *)realloc(*post_tok, sizeof(Token) * (*num_tok));
        (*post_tok)[(*num_tok) - 1].type = OPERATOR;
        strcpy((*post_tok)[(*num_tok) - 1].value, op);
        free(op);
    }
    stack_free(&op_stek);
}
