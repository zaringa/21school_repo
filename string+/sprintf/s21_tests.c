#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

// Тесты для s21_strchr
START_TEST(test_strchr_1) {
  char str[] = "0123456789101112131415161718192021";
  int c = '4';
  char *pointer1 = s21_strchr(str, c);
  char *pointer2 = strchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strchr_2) {
  char str[] = "hi! hello! good morning!";
  int c = 'a';
  char *pointer1 = s21_strchr(str, c);
  char *pointer2 = strchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strchr_3) {
  char str[] = "oyoyoyoyoyoyoyoy";
  int c = 'o';
  char *pointer1 = s21_strchr(str, c);
  char *pointer2 = strchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strchr_4) {
  char str[] = "";
  int c = '!';
  char *pointer1 = s21_strchr(str, c);
  char *pointer2 = strchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strchr_5) {
  char str[] = "pupupupupupuup";
  int c = 0;
  char *pointer1 = s21_strchr(str, c);
  char *pointer2 = strchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strchr_6) {
  char str[] = "Hi! How are you? I hope you're well :)";
  int c = 255;
  char *pointer1 = s21_strchr(str, c);
  char *pointer2 = strchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

Suite *test_suite_strchr(void) {
  Suite *suite = suite_create("s21_strchr");
  TCase *tcase = tcase_create("s21_strchr_case");

  tcase_add_test(tcase, test_strchr_1);
  tcase_add_test(tcase, test_strchr_2);
  tcase_add_test(tcase, test_strchr_3);
  tcase_add_test(tcase, test_strchr_4);
  tcase_add_test(tcase, test_strchr_5);
  tcase_add_test(tcase, test_strchr_6);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strerror
START_TEST(test_strerror_1) {
  int errnum = 0;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

START_TEST(test_strerror_2) {
  int errnum = 21;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

START_TEST(test_strerror_3) {
  int errnum = 2121;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

START_TEST(test_strerror_4) {
  int errnum = -2121;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

START_TEST(test_strerror_5) {
  int errnum = 1;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

Suite *test_suite_strerror(void) {
  Suite *suite = suite_create("s21_strerror");
  TCase *tcase = tcase_create("s21_strerror_case");

  tcase_add_test(tcase, test_strerror_1);
  tcase_add_test(tcase, test_strerror_2);
  tcase_add_test(tcase, test_strerror_3);
  tcase_add_test(tcase, test_strerror_4);
  tcase_add_test(tcase, test_strerror_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strpbrk
START_TEST(test_strpbrk_1) {
  char str1[] = "ostalos uzhe chut chut";
  char str2[] = "chut chut";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_2) {
  char str1[] = "ostalos uzhe chut chut";
  char str2[] = "o";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_3) {
  char str1[] = "kukuruza segondya";
  char str2[] = "dikiy ogurec";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_4) {
  char str1[] = "dikiy ogurec";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_5) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *test_suite_strpbrk(void) {
  Suite *suite = suite_create("s21_strpbrk");
  TCase *tcase = tcase_create("s21_strpbrk_case");

  tcase_add_test(tcase, test_strpbrk_1);
  tcase_add_test(tcase, test_strpbrk_2);
  tcase_add_test(tcase, test_strpbrk_3);
  tcase_add_test(tcase, test_strpbrk_4);
  tcase_add_test(tcase, test_strpbrk_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strrchr
START_TEST(test_strrchr_1) {
  char str[] = "I love school 21!";
  int c = 'e';
  char *pointer1 = s21_strrchr(str, c);
  char *pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_2) {
  char str[] = "I love school 21!";
  int c = 'A';
  char *pointer1 = s21_strrchr(str, c);
  char *pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_3) {
  char str[] = "";
  int c = '!';
  char *pointer1 = s21_strrchr(str, c);
  char *pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_4) {
  char str[] = "pupupupupupuup";
  int c = 0;
  char *pointer1 = s21_strrchr(str, c);
  char *pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

START_TEST(test_strrchr_5) {
  char str[] = "Hi! How are you? I hope you're well :)";
  int c = 255;
  char *pointer1 = s21_strrchr(str, c);
  char *pointer2 = strrchr(str, c);
  ck_assert_pstr_eq(pointer1, pointer2);
}
END_TEST

Suite *test_suite_strrchr(void) {
  Suite *suite = suite_create("s21_strrchr");
  TCase *tcase = tcase_create("s21_strrchr_case");

  tcase_add_test(tcase, test_strrchr_1);
  tcase_add_test(tcase, test_strrchr_2);
  tcase_add_test(tcase, test_strrchr_3);
  tcase_add_test(tcase, test_strrchr_4);
  tcase_add_test(tcase, test_strrchr_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strstr
START_TEST(test_strstr_1) {
  char str[] = "kak delaa rrr chto delayesh";
  char substr[] = "rrr";
  char *ptr1 = strstr(str, substr);
  char *ptr2 = s21_strstr(str, substr);
  ck_assert_pstr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_strstr_2) {
  char str[] = "kak delaa rrr chto delayesh";
  char substr[] = "cucumber";
  char *ptr1 = strstr(str, substr);
  char *ptr2 = s21_strstr(str, substr);
  ck_assert_pstr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_strstr_3) {
  char str[] = "";
  char substr[] = "rrrrrrrr";
  char *ptr1 = strstr(str, substr);
  char *ptr2 = s21_strstr(str, substr);
  ck_assert_pstr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_strstr_4) {
  char str[] = "";
  char substr[] = "";
  char *ptr1 = strstr(str, substr);
  char *ptr2 = s21_strstr(str, substr);
  ck_assert_pstr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_strstr_5) {
  char str[] = "lalalallalalaal";
  char substr[] = "lalalallalalaal";
  char *ptr1 = strstr(str, substr);
  char *ptr2 = s21_strstr(str, substr);
  ck_assert_pstr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(test_strstr_6) {
  char str[] = "bu ispugalsya ne boysya";
  char substr[] = "  ";
  char *ptr1 = strstr(str, substr);
  char *ptr2 = s21_strstr(str, substr);
  ck_assert_pstr_eq(ptr1, ptr2);
}
END_TEST

Suite *test_suite_strstr(void) {
  Suite *suite = suite_create("s21_strstr");
  TCase *tcase = tcase_create("s21_strstr_case");

  tcase_add_test(tcase, test_strstr_1);
  tcase_add_test(tcase, test_strstr_2);
  tcase_add_test(tcase, test_strstr_3);
  tcase_add_test(tcase, test_strstr_4);
  tcase_add_test(tcase, test_strstr_5);
  tcase_add_test(tcase, test_strstr_6);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strtok
START_TEST(test_strtok_1) {
  char str1[] = "i hope this projecy will be complete, please!";
  char str2[] = "i hope this projecy will be complete, please!";
  const char delimeter[] = " ,!";
  char *res_lib = strtok(str1, delimeter);
  char *my_res = s21_strtok(str2, delimeter);
  ck_assert_pstr_eq(my_res, res_lib);
}
END_TEST

START_TEST(test_strtok_2) {
  char str1[] = "i hope this projecy will be complete";
  char str2[] = "i hope this projecy will be complete";
  const char delimeter[] = "!!";
  char *res_lib = strtok(str1, delimeter);
  char *my_res = s21_strtok(str2, delimeter);
  ck_assert_pstr_eq(my_res, res_lib);
}
END_TEST

START_TEST(test_strtok_3) {
  char str1[] = "heeey i'm a little bit tired";
  char str2[] = "heeey i'm a little bit tired";
  const char delimeter[] = " ";
  char *res_lib = strtok(str1, delimeter);
  char *my_res = s21_strtok(str2, delimeter);
  ck_assert_pstr_eq(my_res, res_lib);
  res_lib = strtok(NULL, delimeter);
  my_res = s21_strtok(NULL, delimeter);
  ck_assert_pstr_eq(my_res, res_lib);
  res_lib = strtok(NULL, delimeter);
  my_res = s21_strtok(NULL, delimeter);
  ck_assert_pstr_eq(my_res, res_lib);
}
END_TEST

START_TEST(test_strtok_4) {
  char str1[] = "I love school 21! <3";
  char str2[] = "I love school 21! <3";
  const char delimeter[] = "21! ";
  char *res_lib = strtok(str1, delimeter);
  char *my_res = s21_strtok(str2, delimeter);
  ck_assert_pstr_eq(my_res, res_lib);
}
END_TEST

START_TEST(test_strtok_5) {
  char str1[] = "I love school 21! <3";
  char str2[] = "I love school 21! <3";
  const char delimeter[] = "<";
  char *res_lib = strtok(str1, delimeter);
  char *my_res = s21_strtok(str2, delimeter);
  ck_assert_pstr_eq(my_res, res_lib);
}
END_TEST

Suite *test_suite_strtok(void) {
  Suite *suite = suite_create("s21_strtok");
  TCase *tcase = tcase_create("s21_strtok_case");

  tcase_add_test(tcase, test_strtok_1);
  tcase_add_test(tcase, test_strtok_2);
  tcase_add_test(tcase, test_strtok_3);
  tcase_add_test(tcase, test_strtok_4);
  tcase_add_test(tcase, test_strtok_5);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_to_upper
START_TEST(test_to_upper_1) {
  char vod[] = "small to big";
  char pol[] = "SMALL TO BIG";
  char *program = s21_to_upper(vod);
  ck_assert_str_eq(program, pol);
  if (program) free(program);
}
END_TEST

START_TEST(test_to_upper_2) {
  char vod_2[] = "BIG TO BIG";
  char pol_2[] = "BIG TO BIG";
  char *program_2 = s21_to_upper(vod_2);
  ck_assert_str_eq(program_2, pol_2);
  if (program_2) free(program_2);
}
END_TEST

START_TEST(test_to_upper_3) {
  char vod_3[] = "Small ANd BIg to BIG";
  char pol_3[] = "SMALL AND BIG TO BIG";
  char *program_3 = s21_to_upper(vod_3);
  ck_assert_str_eq(program_3, pol_3);
  if (program_3) free(program_3);
}
END_TEST

Suite *test_suite_to_upper(void) {
  Suite *s = suite_create("s21_to_upper");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_upper_1);
  tcase_add_test(tc_core, test_to_upper_2);
  tcase_add_test(tc_core, test_to_upper_3);

  suite_add_tcase(s, tc_core);
  return s;
}

// Тесты для s21_to_lower
START_TEST(test_to_lower_1) {
  char vod[] = "BIG TO SMALL";
  char pol[] = "big to small";
  char *program = s21_to_lower(vod);
  ck_assert_str_eq(program, pol);
  if (program) free(program);
}
END_TEST

START_TEST(test_to_lower_2) {
  char vod_2[] = "small to small";
  char pol_2[] = "small to small";
  char *program_2 = s21_to_lower(vod_2);
  ck_assert_str_eq(program_2, pol_2);
  if (program_2) free(program_2);
}
END_TEST

START_TEST(test_to_lower_3) {
  char vod_3[] = "BIG And small To small";
  char pol_3[] = "big and small to small";
  char *program_3 = s21_to_lower(vod_3);
  ck_assert_str_eq(program_3, pol_3);
  if (program_3) free(program_3);
}
END_TEST

Suite *test_suite_to_lower(void) {
  Suite *s = suite_create("s21_to_lower");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_to_lower_1);
  tcase_add_test(tc_core, test_to_lower_2);
  tcase_add_test(tc_core, test_to_lower_3);

  suite_add_tcase(s, tc_core);
  return s;
}

// Тесты для s21_insert
START_TEST(test_s21_insert_1) {
  char str1[] = "School";
  char str2[] = "I love  21! <3";
  s21_size_t index = 7;
  char expected[] = "I love School 21! <3";
  char *got = (char *)s21_insert(str2, str1, index);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_2) {
  char str1[] = "hello, ";
  char str2[] = "testirovchik!";
  s21_size_t index = 0;
  char expected[] = "hello, testirovchik!";
  char *got = (char *)s21_insert(str2, str1, index);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_3) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t index = 100;
  char *expected = S21_NULL;
  char *got = (char *)s21_insert(str2, str1, index);
  ck_assert_pstr_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_4) {
  char *str2 = NULL;
  char *str1 = NULL;
  s21_size_t index = 100;
  char *expected = NULL;
  char *got = (char *)s21_insert(str2, str1, index);
  ck_assert_ptr_eq(got, expected);
}
END_TEST

START_TEST(test_s21_insert_5) {
  char str1[] = "Monkey";
  char str2[] = "Di Luffi";
  s21_size_t index = 8;
  char expected[] = "Di LuffiMonkey";
  char *got = (char *)s21_insert(str2, str1, index);
  ck_assert_str_eq(got, expected);
}

START_TEST(test_s21_insert_6) {
  char *str1 = S21_NULL;
  char str2[] = "Kosmos  ";
  s21_size_t index = 6;
  void *expected = S21_NULL;
  char *got = (char *)s21_insert(str2, str1, index);
  ck_assert_pstr_eq(got, expected);
}
END_TEST

Suite *test_suite_insert(void) {
  Suite *s = suite_create("s21_insert");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_insert_1);
  tcase_add_test(tc_core, test_s21_insert_2);
  tcase_add_test(tc_core, test_s21_insert_3);
  tcase_add_test(tc_core, test_s21_insert_4);
  tcase_add_test(tc_core, test_s21_insert_5);
  tcase_add_test(tc_core, test_s21_insert_6);

  suite_add_tcase(s, tc_core);

  return s;
}

// Тесты для s21_trim
START_TEST(test_s21_trim_1) {
  char str1[] = "42I Love School 42 21! <342";
  char str2[] = "42";
  ck_assert_str_eq(s21_trim(str1, str2), "I Love School 42 21! <3");
}

START_TEST(test_s21_trim_2) {
  char str1[] = " NEAR FINAL ";
  char str2[] = " ";
  ck_assert_str_eq(s21_trim(str1, str2), "NEAR FINAL");
}
END_TEST

START_TEST(test_s21_trim_3) {
  char str1[] = "   AAA   ";
  char str2[] = " ";
  ck_assert_str_eq(s21_trim(str1, str2), "AAA");
}
END_TEST

START_TEST(test_s21_trim_4) {
  char str1[] = "aaa";
  char str2[] = "a";
  ck_assert_str_eq(s21_trim(str1, str2), "");
}
END_TEST

START_TEST(test_s21_trim_5) {
  char str1[] = "tuchOstalos chut";
  char str2[] = "tuch ";
  ck_assert_str_eq(s21_trim(str1, str2), "Ostalos");
}

Suite *test_suite_trim(void) {
  Suite *s = suite_create("s21_trim");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_trim_1);
  tcase_add_test(tc_core, test_s21_trim_2);
  tcase_add_test(tc_core, test_s21_trim_3);
  tcase_add_test(tc_core, test_s21_trim_4);
  tcase_add_test(tc_core, test_s21_trim_5);

  suite_add_tcase(s, tc_core);

  return s;
}

// Тесты для s21_memchr
START_TEST(test_memchr_1) {
  char str[] = "Hello world";
  int c = 'o';
  size_t n = 5;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_memchr_2) {
  char str[] = "Hello world";
  int c = 'z';
  size_t n = 11;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_memchr_3) {
  char str[] = "Hello world";
  int c = '\0';
  size_t n = 12;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_memchr_4) {
  char *str = NULL;
  int c = 'a';
  size_t n = 5;
  ck_assert_ptr_eq(s21_memchr(str, c, n), NULL);
}
END_TEST

Suite *test_suite_memchr(void) {
  Suite *suite = suite_create("s21_memchr");
  TCase *tcase = tcase_create("s21_memchr_case");

  tcase_add_test(tcase, test_memchr_1);
  tcase_add_test(tcase, test_memchr_2);
  tcase_add_test(tcase, test_memchr_3);
  tcase_add_test(tcase, test_memchr_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_memcmp
START_TEST(test_memcmp_1) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  size_t n = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_2) {
  char str1[] = "Hello";
  char str2[] = "Hellp";
  size_t n = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_3) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  size_t n = 0;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_memcmp_4) {
  char str1[] = "Hello";
  char str2[] = "Hellp";
  size_t n = 4;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

Suite *test_suite_memcmp(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tcase = tcase_create("s21_memcmp_case");

  tcase_add_test(tcase, test_memcmp_1);
  tcase_add_test(tcase, test_memcmp_2);
  tcase_add_test(tcase, test_memcmp_3);
  tcase_add_test(tcase, test_memcmp_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_memcpy
START_TEST(test_memcpy_1) {
  char src[] = "Hello";
  char dest1[10] = {0};
  char dest2[10] = {0};
  size_t n = 5;
  s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_2) {
  char src[] = "Hello world";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 11;
  s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_3) {
  char src[] = "";
  char dest1[10] = {0};
  char dest2[10] = {0};
  size_t n = 0;
  s21_memcpy(dest1, src, n);
  memcpy(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

Suite *test_suite_memcpy(void) {
  Suite *suite = suite_create("s21_memcpy");
  TCase *tcase = tcase_create("s21_memcpy_case");

  tcase_add_test(tcase, test_memcpy_1);
  tcase_add_test(tcase, test_memcpy_2);
  tcase_add_test(tcase, test_memcpy_3);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_memset
START_TEST(test_memset_1) {
  char str1[10] = "Hello";
  char str2[10] = "Hello";
  int c = 'a';
  size_t n = 3;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_memset_2) {
  char str1[10] = "Hello";
  char str2[10] = "Hello";
  int c = 'b';
  size_t n = 5;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_memset_3) {
  char str1[10] = "";
  char str2[10] = "";
  int c = 'c';
  size_t n = 0;
  s21_memset(str1, c, n);
  memset(str2, c, n);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *test_suite_memset(void) {
  Suite *suite = suite_create("s21_memset");
  TCase *tcase = tcase_create("s21_memset_case");

  tcase_add_test(tcase, test_memset_1);
  tcase_add_test(tcase, test_memset_2);
  tcase_add_test(tcase, test_memset_3);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strncat
START_TEST(test_strncat_1) {
  char dest1[20] = "Hello";
  char dest2[20] = "Hello";
  char src[] = " world";
  size_t n = 6;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_2) {
  char dest1[20] = "";
  char dest2[20] = "";
  char src[] = "world";
  size_t n = 5;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_3) {
  char dest1[20] = "Hello";
  char dest2[20] = "Hello";
  char src[] = "";
  size_t n = 0;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

Suite *test_suite_strncat(void) {
  Suite *suite = suite_create("s21_strncat");
  TCase *tcase = tcase_create("s21_strncat_case");

  tcase_add_test(tcase, test_strncat_1);
  tcase_add_test(tcase, test_strncat_2);
  tcase_add_test(tcase, test_strncat_3);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strncmp
START_TEST(test_strncmp_1) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_2) {
  char str1[] = "Hello";
  char str2[] = "Hellp";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_3) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  size_t n = 0;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_strncmp_4) {
  char str1[] = "Hello";
  char str2[] = "Hellp";
  size_t n = 4;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

Suite *test_suite_strncmp(void) {
  Suite *suite = suite_create("s21_strncmp");
  TCase *tcase = tcase_create("s21_strncmp_case");

  tcase_add_test(tcase, test_strncmp_1);
  tcase_add_test(tcase, test_strncmp_2);
  tcase_add_test(tcase, test_strncmp_3);
  tcase_add_test(tcase, test_strncmp_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strncpy
START_TEST(test_strncpy_1) {
  char src[] = "Hello";
  char dest1[10] = {0};
  char dest2[10] = {0};
  size_t n = 5;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_2) {
  char src[] = "Hello world";
  char dest1[20] = {0};
  char dest2[20] = {0};
  size_t n = 11;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_3) {
  char src[] = "";
  char dest1[10] = {0};
  char dest2[10] = {0};
  size_t n = 0;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

Suite *test_suite_strncpy(void) {
  Suite *suite = suite_create("s21_strncpy");
  TCase *tcase = tcase_create("s21_strncpy_case");

  tcase_add_test(tcase, test_strncpy_1);
  tcase_add_test(tcase, test_strncpy_2);
  tcase_add_test(tcase, test_strncpy_3);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strcspn
START_TEST(test_strcspn_1) {
  char str[] = "Hello world";
  char chars[] = " ";
  ck_assert_int_eq(s21_strcspn(str, chars), strcspn(str, chars));
}
END_TEST

START_TEST(test_strcspn_2) {
  char str[] = "Hello world";
  char chars[] = "xyz";
  ck_assert_int_eq(s21_strcspn(str, chars), strcspn(str, chars));
}
END_TEST

START_TEST(test_strcspn_3) {
  char str[] = "Hello world";
  char chars[] = "H";
  ck_assert_int_eq(s21_strcspn(str, chars), strcspn(str, chars));
}
END_TEST

START_TEST(test_strcspn_4) {
  char str[] = "";
  char chars[] = "abc";
  ck_assert_int_eq(s21_strcspn(str, chars), strcspn(str, chars));
}
END_TEST

Suite *test_suite_strcspn(void) {
  Suite *suite = suite_create("s21_strcspn");
  TCase *tcase = tcase_create("s21_strcspn_case");

  tcase_add_test(tcase, test_strcspn_1);
  tcase_add_test(tcase, test_strcspn_2);
  tcase_add_test(tcase, test_strcspn_3);
  tcase_add_test(tcase, test_strcspn_4);

  suite_add_tcase(suite, tcase);
  return suite;
}

// Тесты для s21_strlen
START_TEST(test_strlen_1) {
  char str[] = "Hello";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_2) {
  char str[] = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_3) {
  char str[] = "Hello world!";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *test_suite_strlen(void) {
  Suite *suite = suite_create("s21_strlen");
  TCase *tcase = tcase_create("s21_strlen_case");

  tcase_add_test(tcase, test_strlen_1);
  tcase_add_test(tcase, test_strlen_2);
  tcase_add_test(tcase, test_strlen_3);

  suite_add_tcase(suite, tcase);
  return suite;
}

int main(void) {
  int failed = 0;
  Suite *s;
  SRunner *sr;

  // Тесты для s21_strchr
  s = test_suite_strchr();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strerror
  s = test_suite_strerror();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strpbrk
  s = test_suite_strpbrk();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strrchr
  s = test_suite_strrchr();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strstr
  s = test_suite_strstr();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strtok
  s = test_suite_strtok();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_to_upper
  s = test_suite_to_upper();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_to_lower
  s = test_suite_to_lower();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_insert
  s = test_suite_insert();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_trim
  s = test_suite_trim();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_memchr
  s = test_suite_memchr();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_memcmp
  s = test_suite_memcmp();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_memcpy
  s = test_suite_memcpy();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_memset
  s = test_suite_memset();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strncat
  s = test_suite_strncat();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strncmp
  s = test_suite_strncmp();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strncpy
  s = test_suite_strncpy();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strcspn
  s = test_suite_strcspn();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  // Тесты для s21_strlen
  s = test_suite_strlen();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? 0 : 1;
}