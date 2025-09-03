#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <wchar.h>

#include "sprintf.h"

void test_int_setup(long long num, const char *token, char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, num);
  s21_sprintf(buf2, token, num);
  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_int_100) {
  const char *tokens[] = {"%d",
                          "Hello %d World!",
                          "Hello %10d World!",
                          "Hello %.5d World!",
                          "Hello %10.5d World!",
                          "aaa %-10d aaa",
                          "bbb%-10.5daa",
                          "ccc %+.5d",
                          "ccc %+10d",
                          "ccc %+10.5d",
                          "aaa %0d aaa",
                          "bbb %-0d aaa",
                          "bbb %-0.5d aaa",
                          "bbb %-010.5d aaa",
                          "ddd % d aaa",
                          "eee % 10d asd",
                          "asd % 5.3d asd",
                          "asd % 02.3d asd",
                          "asd %hd asd",
                          "asd %ld asd"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_int_setup(100, tokens[i], "test_int_100");
  }
}
END_TEST

START_TEST(test_int_neg100) {
  const char *tokens[] = {"%d",
                          "Hello %d World!",
                          "Hello %10d World!",
                          "Hello %.5d World!",
                          "Hello %10.5d World!",
                          "aaa %-10d aaa",
                          "bbb%-10.5daa",
                          "ccc %+.5d",
                          "ccc %+10d",
                          "ccc %+10.5d",
                          "aaa %0d aaa",
                          "bbb %-0d aaa",
                          "bbb %-0.5d aaa",
                          "bbb %-010.5d aaa",
                          "ddd % d aaa",
                          "eee % 10d asd",
                          "asd % 5.3d asd",
                          "asd % 02.3d asd",
                          "asd %hd asd",
                          "asd %ld asd"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_int_setup(-100, tokens[i], "test_int_neg100");
  }
}
END_TEST

START_TEST(test_int_shrt_max_plus1) {
  const char *tokens[] = {"%d",
                          "Hello %d World!",
                          "Hello %10d World!",
                          "Hello %.5d World!",
                          "Hello %10.5d World!",
                          "aaa %-10d aaa",
                          "bbb%-10.5daa",
                          "ccc %+.5d",
                          "ccc %+10d",
                          "ccc %+10.5d",
                          "aaa %0d aaa",
                          "bbb %-0d aaa",
                          "bbb %-0.5d aaa",
                          "bbb %-010.5d aaa",
                          "ddd % d aaa",
                          "eee % 10d asd",
                          "asd % 5.3d asd",
                          "asd % 02.3d asd",
                          "asd %hd asd",
                          "asd %ld asd"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_int_setup(SHRT_MAX + 1, tokens[i], "test_int_shrt_max_plus1");
  }
}
END_TEST

START_TEST(test_int_shrt_min_minus1) {
  const char *tokens[] = {"%d",
                          "Hello %d World!",
                          "Hello %10d World!",
                          "Hello %.5d World!",
                          "Hello %10.5d World!",
                          "aaa %-10d aaa",
                          "bbb%-10.5daa",
                          "ccc %+.5d",
                          "ccc %+10d",
                          "ccc %+10.5d",
                          "aaa %0d aaa",
                          "bbb %-0d aaa",
                          "bbb %-0.5d aaa",
                          "bbb %-010.5d aaa",
                          "ddd % d aaa",
                          "eee % 10d asd",
                          "asd % 5.3d asd",
                          "asd % 02.3d asd",
                          "asd %hd asd",
                          "asd %ld asd"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_int_setup(SHRT_MIN - 1, tokens[i], "test_int_shrt_min_minus1");
  }
}
END_TEST

START_TEST(test_int_int_max_plus1) {
  const char *tokens[] = {"%d",
                          "Hello %d World!",
                          "Hello %10d World!",
                          "Hello %.5d World!",
                          "Hello %10.5d World!",
                          "aaa %-10d aaa",
                          "bbb%-10.5daa",
                          "ccc %+.5d",
                          "ccc %+10d",
                          "ccc %+10.5d",
                          "aaa %0d aaa",
                          "bbb %-0d aaa",
                          "bbb %-0.5d aaa",
                          "bbb %-010.5d aaa",
                          "ddd % d aaa",
                          "eee % 10d asd",
                          "asd % 5.3d asd",
                          "asd % 02.3d asd",
                          "asd %hd asd",
                          "asd %ld asd"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_int_setup((long long)INT_MAX + 1, tokens[i], "test_int_int_max_plus1");
  }
}
END_TEST

START_TEST(test_int_int_min_minus1) {
  const char *tokens[] = {"%d",
                          "Hello %d World!",
                          "Hello %10d World!",
                          "Hello %.5d World!",
                          "Hello %10.5d World!",
                          "aaa %-10d aaa",
                          "bbb%-10.5daa",
                          "ccc %+.5d",
                          "ccc %+10d",
                          "ccc %+10.5d",
                          "aaa %0d aaa",
                          "bbb %-0d aaa",
                          "bbb %-0.5d aaa",
                          "bbb %-010.5d aaa",
                          "ddd % d aaa",
                          "eee % 10d asd",
                          "asd % 5.3d asd",
                          "asd % 02.3d asd",
                          "asd %hd asd",
                          "asd %ld asd"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_int_setup((long long)INT_MIN - 1, tokens[i],
                   "test_int_int_min_minus1");
  }
}
END_TEST

void test_uint_octal_setup(unsigned long long num, const char *token,
                           char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, num);
  s21_sprintf(buf2, token, num);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_uint_octal_100) {
  const char *tokens[] = {"%o",
                          "Hello %o World!",
                          "Hello %10o World!",
                          "Hello %.5o World!",
                          "Hello %10.5o World!",
                          "aaa %-10o aaa",
                          "bbb%-10.5oaa",
                          "ccc %+.5o",
                          "ccc %+10o",
                          "ccc %+10.5o",
                          "aaa %0o aaa",
                          "bbb %-0o aaa",
                          "bbb %-0.5o aaa",
                          "bbb %-010.5o aaa",
                          "ddd % o aaa",
                          "eee % 10o asd",
                          "asd % 5.3o asd",
                          "asd % 02.3o asd",
                          "asd %ho asd",
                          "asd %lo asd",
                          "asd %#o"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_uint_octal_setup(100, tokens[i], "test_uint_octal_100");
  }
}
END_TEST

void test_uint_hexadecimal_setup(unsigned long long num, const char *token,
                                 char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, num);
  s21_sprintf(buf2, token, num);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_uint_hexadecimal_100) {
  const char *tokens[] = {"%x",
                          "Hello %X World!",
                          "Hello %10x World!",
                          "Hello %.5x World!",
                          "Hello %10.5X World!",
                          "aaa %-10x aaa",
                          "bbb%-10.5xaa",
                          "ccc %+.5x",
                          "ccc %+10x",
                          "ccc %+10.5x",
                          "aaa %0x aaa",
                          "bbb %-0x aaa",
                          "bbb %-0.5X aaa",
                          "bbb %-010.5X aaa",
                          "ddd % X aaa",
                          "eee % 10X asd",
                          "asd % 5.3X asd",
                          "asd % 02.3X asd",
                          "asd %hX asd",
                          "asd %lX asd",
                          "asd %#x"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_uint_hexadecimal_setup(100, tokens[i], "test_uint_hexadecimal_100");
  }
}
END_TEST

void test_fp_decimal_setup(double num, double num2, const char *token,
                           char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, num, num2);
  s21_sprintf(buf2, token, num, num2);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_fp_decimal_0_156) {
  const char *tokens[] = {"%f",
                          "Hello %f World!",
                          "Hello %10f World!",
                          "Hello %.5f World!",
                          "Hello %10.5f World!",
                          "aaa %-10f aaa",
                          "bbb%-.10foaa",
                          "ccc %+.5f",
                          "ccc %+10f",
                          "ccc %+10.5f",
                          "aaa %0f aaa",
                          "bbb %-0f aaa",
                          "bbb %-0.5f aaa",
                          "bbb %-010.5f aaa",
                          "ddd % f aaa",
                          "eee % 10f asd",
                          "asd % 5.3f asd",
                          "asd % 02.3f asd",
                          "asd %f asd %f",
                          "asd %lf asd %f"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_fp_decimal_setup(0.156, -1.156, tokens[i], "test_fp_decimal_0_156");
  }
}
END_TEST

START_TEST(test_fp_decimal_neg1_156) {
  const char *tokens[] = {"%f",
                          "Hello %f World!",
                          "Hello %10f World!",
                          "Hello %.5f World!",
                          "Hello %10.5f World!",
                          "aaa %-10f aaa",
                          "bbb%-.10foaa",
                          "ccc %+.5f",
                          "ccc %+10f",
                          "ccc %+10.5f",
                          "aaa %0f aaa",
                          "bbb %-0f aaa",
                          "bbb %-0.5f aaa",
                          "bbb %-010.5f aaa",
                          "ddd % f aaa",
                          "eee % 10f asd",
                          "asd % 5.3f asd",
                          "asd % 02.3f asd",
                          "asd %f asd %f",
                          "asd %lf asd %f"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_fp_decimal_setup(-1.156, 0.156, tokens[i], "test_fp_decimal_neg1_156");
  }
}
END_TEST

void test_fp_scientific_setup(double num, double num2, const char *token,
                              char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, num, num2);
  s21_sprintf(buf2, token, num, num2);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_fp_scientific_0_156) {
  const char *tokens[] = {"%e",
                          "Hello %E World!",
                          "Hello %10e World!",
                          "Hello %.5E World!",
                          "Hello %10.5e World!",
                          "aaa %-10E aaa",
                          "bbb%-.10eoaa",
                          "ccc %+.5e",
                          "ccc %+10e",
                          "ccc %+10.5e",
                          "aaa %0e aaa",
                          "bbb %-0e aaa",
                          "bbb %-0.5e aaa",
                          "bbb %-010.5e aaa",
                          "ddd % e aaa",
                          "eee % 10e asd",
                          "asd % 5.3e asd",
                          "asd % 02.3e asd",
                          "asd %e asd %e",
                          "asd %le asd %e"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_fp_scientific_setup(0.156, -1.156, tokens[i],
                             "test_fp_scientific_0_156");
  }
}
END_TEST

START_TEST(test_fp_scientific_neg1_156) {
  const char *tokens[] = {"%e",
                          "Hello %E World!",
                          "Hello %10e World!",
                          "Hello %.5E World!",
                          "Hello %10.5e World!",
                          "aaa %-10E aaa",
                          "bbb%-.10eoaa",
                          "ccc %+.5e",
                          "ccc %+10e",
                          "ccc %+10.5e",
                          "aaa %0e aaa",
                          "bbb %-0e aaa",
                          "bbb %-0.5e aaa",
                          "bbb %-010.5e aaa",
                          "ddd % e aaa",
                          "eee % 10e asd",
                          "asd % 5.3e asd",
                          "asd % 02.3e asd",
                          "asd %e asd %e",
                          "asd %le asd %e"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_fp_scientific_setup(-1.156, 0.156, tokens[i],
                             "test_fp_scientific_neg1_156");
  }
}
END_TEST

void test_pointer_setup(int *ptr, const char *token, char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, ptr);
  s21_sprintf(buf2, token, ptr);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_pointer) {
  int number = 1;
  const char *tokens[] = {"%p", "Hello %p world!"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_pointer_setup(&number, tokens[i], "test_pointer");
  }
}
END_TEST

void test_char_setup(char c, const char *token, char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, c);
  s21_sprintf(buf2, token, c);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_char_a) {
  const char *tokens[] = {"%c", "%5c"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_char_setup('a', tokens[i], "test_char_a");
  }
}
END_TEST

void test_wchar_setup(wchar_t c, const char *token, char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, c);
  s21_sprintf(buf2, token, c);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_wchar_a) {
  const char *tokens[] = {"test%lc test", "test%10lctest"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    test_wchar_setup(L'a', tokens[i], "test_wchar_a");
  }
}
END_TEST

void test_string_setup(const char *str, const char *token, char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, str);
  s21_sprintf(buf2, token, str);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_string) {
  const char *tokens[] = {"test%s test", "test%10sctest", "asd %.7s"};
  const char *strs[] = {"Hello!!", "123123123"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    for (int j = 0; j < (int)(sizeof(strs) / sizeof(char *)); j++) {
      test_string_setup(strs[j], tokens[i], "test_string");
    }
  }
}
END_TEST

void test_wstring_setup(const wchar_t *str, const char *token,
                        char *test_name) {
  char buf1[1024];
  char buf2[1024];
  sprintf(buf1, token, str);
  s21_sprintf(buf2, token, str);

  (void)test_name;
  ck_assert_str_eq(buf1, buf2);
}

START_TEST(test_wstring) {
  const char *tokens[] = {"test%ls test", "test%10lsctest", "asd %.7ls"};
  const wchar_t *strs[] = {L"Hello!!", L"123123123"};
  for (int i = 0; i < (int)(sizeof(tokens) / sizeof(char *)); i++) {
    for (int j = 0; j < (int)(sizeof(strs) / sizeof(wchar_t *)); j++) {
      test_wstring_setup(strs[j], tokens[i], "test_wstring");
    }
  }
}
END_TEST

Suite *sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc_int = tcase_create("Int");
  TCase *tc_uint_octal = tcase_create("Uint_Octal");
  TCase *tc_uint_hex = tcase_create("Uint_Hex");
  TCase *tc_fp_decimal = tcase_create("FP_Decimal");
  TCase *tc_fp_scientific = tcase_create("FP_Scientific");
  TCase *tc_pointer = tcase_create("Pointer");
  TCase *tc_char = tcase_create("Char");
  TCase *tc_wchar = tcase_create("WChar");
  TCase *tc_string = tcase_create("String");
  TCase *tc_wstring = tcase_create("WString");

  tcase_add_test(tc_int, test_int_100);
  tcase_add_test(tc_int, test_int_neg100);
  tcase_add_test(tc_int, test_int_shrt_max_plus1);
  tcase_add_test(tc_int, test_int_shrt_min_minus1);
  tcase_add_test(tc_int, test_int_int_max_plus1);
  tcase_add_test(tc_int, test_int_int_min_minus1);
  tcase_add_test(tc_uint_octal, test_uint_octal_100);
  tcase_add_test(tc_uint_hex, test_uint_hexadecimal_100);
  tcase_add_test(tc_fp_decimal, test_fp_decimal_0_156);
  tcase_add_test(tc_fp_decimal, test_fp_decimal_neg1_156);
  tcase_add_test(tc_fp_scientific, test_fp_scientific_0_156);
  tcase_add_test(tc_fp_scientific, test_fp_scientific_neg1_156);
  tcase_add_test(tc_pointer, test_pointer);
  tcase_add_test(tc_char, test_char_a);
  tcase_add_test(tc_wchar, test_wchar_a);
  tcase_add_test(tc_string, test_string);
  tcase_add_test(tc_wstring, test_wstring);

  suite_add_tcase(s, tc_int);
  suite_add_tcase(s, tc_uint_octal);
  suite_add_tcase(s, tc_uint_hex);
  suite_add_tcase(s, tc_fp_decimal);
  suite_add_tcase(s, tc_fp_scientific);
  suite_add_tcase(s, tc_pointer);
  suite_add_tcase(s, tc_char);
  suite_add_tcase(s, tc_wchar);
  suite_add_tcase(s, tc_string);
  suite_add_tcase(s, tc_wstring);

  return s;
}

int main(void) {
  Suite *s = sprintf_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failures = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failures == 0) ? 0 : 1;
}
