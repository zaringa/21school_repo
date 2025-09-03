#ifndef GRATH_H
#define GRATH_H
#include "bobir.h"

void print_graph(int matrix[HEIGHT][WIDTH]);
void work_work(int matrix[HEIGHT][WIDTH], const Token *post_tok, int num_tok);
void grr(int matrix[HEIGHT][WIDTH]);

int precedence(const char *op);
void num_var(Token **post_tok, int *num_post_tok, const Token *cur_tok);
void un_mi_2(const Token *inf_tok, Token **post_tok, int *num_tok, int *i);
void no_min(Stack *op_stack, Token **post_tok, int *num_post_tok, const Token *cur_tok);
void rt_bb(Stack *op_stack, Token **post_tok, int *num_post_tok);
void inf_cur(const Token *inf_tok, int num_inf_tok, Token **post_tok, int *num_post_tok);

#endif