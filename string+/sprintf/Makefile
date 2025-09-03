CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TEST_LIBS = $(shell pkg-config --libs --cflags check)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -lm

SRC_DIR = s21_all_functions
SPRINTF_DIR = sprintf
LIB_NAME = s21_string.a
STRING_TEST = test_s21_string
SPRINTF_TEST = test_s21_sprintf
GCOV_DIR = gcov_report

LIB_SRCS = $(SRC_DIR)/s21_functions_kacyfare.c \
           $(SRC_DIR)/s21_functions_prawnsir.c \
           $(SRC_DIR)/s21_special_functions.c \
           $(SRC_DIR)/s21_strerror.c

SPRINTF_SRCS = $(SPRINTF_DIR)/flat_map/flat_map.c \
               $(SPRINTF_DIR)/functions.c \
               $(SPRINTF_DIR)/grisu/grisu3.c \
							 $(SPRINTF_DIR)/sprintf.c

STRING_TEST_SRC = s21_tests.c $(SPRINTF_SRCS)
SPRINTF_TEST_SRC = $(SPRINTF_DIR)/s21_test_sprintf.c

.PHONY: all clean test gcov_report

all: s21_string.a

$(LIB_NAME): $(LIB_SRCS)
	$(CC) $(CFLAGS) -c $^
	ar rcs $@ *.o
	ranlib $@
	@rm -f *.o

test: $(LIB_NAME)
	
	$(CC) $(CFLAGS) $(STRING_TEST_SRC) -o $(STRING_TEST) $(LIB_NAME) $(TEST_LIBS) $(LDFLAGS)
	./$(STRING_TEST)
	
	$(CC) $(CFLAGS) $(SPRINTF_TEST_SRC) $(SPRINTF_SRCS) -o $(SPRINTF_TEST) $(LIB_NAME) $(TEST_LIBS) $(LDFLAGS)
	./$(SPRINTF_TEST)

gcov_report: clean
	@mkdir -p $(GCOV_DIR)
	
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(LIB_SRCS) $(STRING_TEST_SRC) -o $(STRING_TEST) $(TEST_LIBS)
	./$(STRING_TEST) || true
	
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(LIB_SRCS) $(SPRINTF_TEST_SRC) $(SPRINTF_SRCS) -o $(SPRINTF_TEST) $(TEST_LIBS) $(LDFLAGS)
	./$(SPRINTF_TEST) || true
	
	lcov -t "s21_string" -o $(GCOV_DIR)/coverage.info -c -d .
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/coverage.info
	@echo "\nOpen report: $(GCOV_DIR)/index.html"
	@open $(GCOV_DIR)/index.html 2>/dev/null || xdg-open $(GCOV_DIR)/index.html 2>/dev/null || true

clean:
	@rm -rf $(STRING_TEST) $(SPRINTF_TEST) $(LIB_NAME) *.o *.gcda *.gcno *.info $(GCOV_DIR)
