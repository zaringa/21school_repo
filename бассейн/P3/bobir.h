#ifndef BOBIR_H
#define BOBIR_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEIGHT 25
#define WIDTH 80
typedef enum { NUMBER, OPERATOR, FUNCTION, VARIABLE, LEFT_PAREN, RIGHT_PAREN } TokenType;

typedef struct {
    TokenType type;
    char value[50];
} Token;

typedef struct {
    char **data;
    int size;
    int top;
} Stack;

void stack_init(Stack *stack, int size);
int stack_empty(const Stack *stack);
void stack_push(Stack *stack, const char *value);
char *stack_pop(Stack *stack);
char *stack_top(const Stack *stack);
void stack_free(Stack *stack);

void prnum(const char *exp, Token **tokens, int *num_tokens, int *i);
void un_mi(Token **tokens, int *num_tokens, int *i);
void prop(const char *exp, Token **tokens, int *num_tokens, int *i);
void pr_lf(Token **tokens, int *num_tokens, int *i);
void pr_rt(Token **tokens, int *num_tokens, int *i);
void bobr_funct(const char *exp, Token **tokens, int *num_tokens, int *i);
void paex(const char *exp, Token **tokens, int *num_tokens);

double risov_fan(const Token *ps_tok, int num_ps_tok, double x);
char *ftos(double num);
double postfix_ris(const Token *ps_tok, int num_ps_tok, double x);
void fun_oper(const Token *tok, Stack *stach);
void fun_var(const Token *tok, Stack *stach, double x);
void fun_fin(const Token *tok, Stack *stach);

#endif
