#include "bobir.h"

void pr_rt(Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;
    *tokens = (Token *)realloc(*tokens, sizeof(Token) * (*num_tokens));
    (*tokens)[(*num_tokens) - 1].type = RIGHT_PAREN;
    (*tokens)[(*num_tokens) - 1].value[0] = ')';
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';
    *i = *i + 1;
}
void un_mi(Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;
    *tokens = (Token *)realloc(*tokens, sizeof(Token) * (*num_tokens));
    (*tokens)[(*num_tokens) - 1].type = OPERATOR;
    (*tokens)[(*num_tokens) - 1].value[0] = '$';
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';
    *i = *i + 1;
}

void prop(const char *exp, Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;
    *tokens = (Token *)realloc(*tokens, sizeof(Token) * (*num_tokens));
    (*tokens)[(*num_tokens) - 1].type = OPERATOR;
    (*tokens)[(*num_tokens) - 1].value[0] = exp[*i];
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';
    *i = *i + 1;
}

void pr_lf(Token **tokens, int *num_tokens, int *i) {
    (*num_tokens)++;
    *tokens = (Token *)realloc(*tokens, sizeof(Token) * (*num_tokens));
    (*tokens)[(*num_tokens) - 1].type = LEFT_PAREN;
    (*tokens)[(*num_tokens) - 1].value[0] = '(';
    (*tokens)[(*num_tokens) - 1].value[1] = '\0';
    *i = *i + 1;
}

void paex(const char *exp, Token **tokens, int *num_tokens) {
    *num_tokens = 0;
    *tokens = NULL;
    int i = 0;
    while (exp[i] != '\0') {
        if (exp[i] == ' ') {
            i++;
            continue;
        }
        if (exp[i] >= '0' && exp[i] <= '9') {
            prnum(exp, tokens, num_tokens, &i);
        } else if (exp[i] == '-' && exp[i - 1] != ')' &&
                   (i == 0 || exp[i - 1] != (exp[i] >= '0' && exp[i] <= '9'))) {
            un_mi(tokens, num_tokens, &i);
        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            prop(exp, tokens, num_tokens, &i);
        } else if (exp[i] == '(') {
            pr_lf(tokens, num_tokens, &i);
        } else if (exp[i] == ')') {
            pr_rt(tokens, num_tokens, &i);
        } else if ((exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'Z')) {
            bobr_funct(exp, tokens, num_tokens, &i);
        } else {
            i++;
        }
    }
}

void prnum(const char *exp, Token **tokens, int *num_tokens, int *i) {
    int j = 0;

    char num[50] = {'\0'};
    while ((exp[*i] >= '0' && exp[*i] <= '9') || exp[*i] == '.') {
        num[j++] = exp[*i];
        *i = *i + 1;
    }
    (*num_tokens)++;
    *tokens = (Token *)realloc(*tokens, sizeof(Token) * (*num_tokens));
    (*tokens)[(*num_tokens) - 1].type = NUMBER;
    strcpy((*tokens)[(*num_tokens) - 1].value, num);
}
void bobr_funct(const char *exp, Token **tokens, int *num_tokens, int *i) {
    int j = 0;

    char identifier[50] = {'\0'};
    while ((exp[*i] >= 'a' && exp[*i] <= 'z') || (exp[*i] >= 'A' && exp[*i] <= 'Z')) {
        identifier[j++] = exp[*i];
        *i = *i + 1;
    }
    (*num_tokens)++;
    *tokens = (Token *)realloc(*tokens, sizeof(Token) * (*num_tokens));
    if (strcmp(identifier, "sin") == 0 || strcmp(identifier, "cos") == 0 || strcmp(identifier, "tan") == 0 ||
        strcmp(identifier, "ctg") == 0 || strcmp(identifier, "sqrt") == 0 || strcmp(identifier, "ln") == 0) {
        (*tokens)[(*num_tokens) - 1].type = FUNCTION;
    } else {
        (*tokens)[(*num_tokens) - 1].type = VARIABLE;
    }
    strcpy((*tokens)[(*num_tokens) - 1].value, identifier);
}
void stack_init(Stack *stack, int size) {
    stack->data = (char **)malloc(sizeof(char *) * size);
    stack->size = size;
    stack->top = -1;
}

int stack_empty(const Stack *stack) { return stack->top == -1; }

void stack_push(Stack *stack, const char *value) {
    if (stack->top < stack->size - 1) {
        stack->top++;
        stack->data[stack->top] = (char *)malloc(sizeof(char) * (strlen(value) + 1));
        strcpy(stack->data[stack->top], value);
    }
}
char *stack_pop(Stack *stack) {
    char *value = NULL;
    if (!stack_empty(stack)) {
        value = stack->data[stack->top];
        stack->top--;
    }
    return value;
}

char *stack_top(const Stack *stack) {
    char *value = NULL;
    if (!stack_empty(stack)) {
        value = stack->data[stack->top];
    }
    return value;
}

void stack_free(Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        free(stack->data[i]);
    }
    free(stack->data);
}

char *ftos(double num) {
    char *str = (char *)malloc(20);
    snprintf(str, 20, "%lf", num);
    return str;
}
void fun_var(const Token *tok, Stack *stach, double x) {
    if (tok->value[0] == '-') {
        char *ccc = ftos(-x);
        stack_push(stach, ccc);
        free(ccc);
    } else {
        char *ccc = ftos(x);
        stack_push(stach, ccc);
        free(ccc);
    }
}
void fun_oper(const Token *tok, Stack *stach) {
    double op2 = atof(stack_top(stach));
    char *o1 = stack_pop(stach);
    free(o1);
    double op1 = atof(stack_top(stach));
    char *o2 = stack_pop(stach);
    free(o2);

    if (strcmp(tok->value, "+") == 0) {
        char *ccc = ftos(op1 + op2);
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "-") == 0) {
        char *ccc = ftos(op1 - op2);
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "*") == 0) {
        char *ccc = ftos(op1 * op2);
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "/") == 0) {
        char *ccc = ftos(op1 / op2);
        stack_push(stach, ccc);
        free(ccc);
    }
}

void fun_fin(const Token *tok, Stack *stach) {
    double op = atof(stack_top(stach));
    char *c = stack_pop(stach);
    free(c);

    if (strcmp(tok->value, "sin") == 0) {
        char *ccc = ftos(sin(op));
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "cos") == 0) {
        char *ccc = ftos(cos(op));
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "tan") == 0) {
        char *ccc = ftos(tan(op));
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "ctg") == 0) {
        char *ccc = ftos(1.0 / tan(op));
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "sqrt") == 0) {
        char *ccc = ftos(sqrt(op));
        stack_push(stach, ccc);
        free(ccc);
    } else if (strcmp(tok->value, "ln") == 0) {
        char *ccc = ftos(log(op));
        stack_push(stach, ccc);
        free(ccc);
    }
}

double postfix_ris(const Token *ps_tok, int num_ps_tok, double x) {
    Stack stach;
    stack_init(&stach, num_ps_tok);

    for (int i = 0; i < num_ps_tok; i++) {
        const Token *tok = &ps_tok[i];
        if (tok->type == NUMBER) {
            stack_push(&stach, tok->value);
        } else if (tok->type == VARIABLE) {
            fun_var(tok, &stach, x);
        } else if (tok->type == OPERATOR) {
            fun_oper(tok, &stach);
        } else if (tok->type == FUNCTION) {
            fun_fin(tok, &stach);
        }
    }

    double result = atof(stack_top(&stach));
    char *c = stack_pop(&stach);
    free(c);

    stack_free(&stach);
    return result;
}

double risov_fan(const Token *ps_tok, int num_ps_tok, double x) { return postfix_ris(ps_tok, num_ps_tok, x); }