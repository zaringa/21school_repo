.PHONY: state_sort state_search clear_state clear
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

B = ../build/
Q1 = $(B)Quest_1
Q2 = $(B)Quest_2
Q3 = $(B)Quest_3

all: state_sort state_search clear_state clear

state_sort: state_sort.c help.c $(Q1)

$(Q1): state_sort.o help.o
	$(CC) $^ -o $@

state_search: state_search.c help.c $(Q2)

$(Q2): state_search.o help.o
	$(CC) $^ -o $@
clear_state: clear_state.c $(Q3)

$(Q3): clear_state.o
	$(CC) $^ -o $@

clean:
	rm -rf *.o

rebuild: clean all

format: 
	clang-format -i *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem ./