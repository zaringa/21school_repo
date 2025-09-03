#include "grisu3.h"

#include <assert.h>
#include <math.h>
#include <stdint.h>

typedef struct {
  uint64_t f;
  int32_t e;
} diy_fp;

uint64_t as_uint64(double v) {
  union {
    double d;
    uint64_t u;
  } represent;

  represent.d = v;
  return represent.u;
}

void normalize(diy_fp *fp) {
  assert(fp != 0);

  uint64_t significand = fp->f;
  int32_t exponent = fp->e;

  const uint64_t k10MSBits = 0xFFC0000000000000ULL;

  while ((significand & k10MSBits) == 0) {
    significand <<= 10;
    exponent -= 10;
  }

  const uint64_t kUint64MSB = 0x8000000000000000ULL;
  while ((significand & kUint64MSB) == 0) {
    significand <<= 1;
    exponent -= 1;
  }

  fp->e = exponent;
  fp->f = significand;
}

diy_fp multiply(diy_fp fp_1, diy_fp fp_2) {
  diy_fp res;

  const uint64_t kM32 = 0xFFFFFFFFU;
  const uint64_t a = fp_1.f >> 32;
  const uint64_t b = fp_1.f & kM32;
  const uint64_t c = fp_2.f >> 32;
  const uint64_t d = fp_2.f & kM32;
  const uint64_t ac = a * c;
  const uint64_t bc = b * c;
  const uint64_t ad = a * d;
  const uint64_t bd = b * d;

  const uint64_t temp = (bd >> 32) + (ad & kM32) + (bc & kM32) + (1U << 31);
  res.e = fp_1.e + fp_2.e + 64;
  res.f = ac + (ad >> 32) + (bc >> 32) + (temp >> 32);

  return res;
}

diy_fp minus(diy_fp fp_1, diy_fp fp_2) {
  diy_fp res;

  assert(fp_1.e == fp_2.e);
  assert(fp_1.f >= fp_2.f);

  res.e = fp_1.e;
  res.f = fp_1.f - fp_2.f;

  return res;
}

diy_fp get_normalized_diy(double num) {
  assert(num > 0.0);

  diy_fp res;

  uint64_t u_num = as_uint64(num);

  uint64_t significand = GET_SIGNIFICAND(u_num);
  int32_t exponent;

  if (!IS_DENORMAL(u_num)) {
    significand += HIDDEN_BIT;
    exponent = (int)(GET_EXPONENT(u_num) >> 52) - EXPONENT_BIAS;
  } else {
    exponent = DENORMAL_EXPONENT;
  }

  while ((significand & HIDDEN_BIT) == 0) {
    significand <<= 1;
    exponent -= 1;
  }

  significand <<= 11;
  exponent -= 11;

  res.e = exponent;
  res.f = significand;

  return res;
}

diy_fp get_diy(double num) {
  assert(num > 0.0);
  assert(!((as_uint64(num) & EXPONENT_MASK) == EXPONENT_MASK));

  diy_fp res;

  uint64_t u_num = as_uint64(num);

  uint64_t significand = GET_SIGNIFICAND(u_num);
  int32_t exponent;

  if (!IS_DENORMAL(u_num)) {
    significand += HIDDEN_BIT;
    exponent = (int)(GET_EXPONENT(u_num) >> 52) - EXPONENT_BIAS;
  } else {
    exponent = DENORMAL_EXPONENT;
  }

  res.e = exponent;
  res.f = significand;

  return res;
}

void get_cached_for_power_for_binary_exponent_range(int min_exponent,
                                                    int max_exponent,
                                                    diy_fp *power,
                                                    int *decimal_exponent) {
  double k = ceil((min_exponent + DIY_FP_SAGNIFICAND_SIZE - 1) * LOG_10_2);

  int index =
      (CACHED_POWER_OFFSET + (int)k - 1) / DECIMAL_EXPONENT_DISTANCE + 1;

  assert(0 <= index &&
         index < (int)(sizeof(kCachedPowers) / sizeof(kCachedPowers[0])));

  struct CachedPower cached_power = kCachedPowers[index];

  (void)max_exponent;

  *decimal_exponent = cached_power.decimal_exponent;

  diy_fp p;
  p.e = cached_power.binary_exponent;
  p.f = cached_power.significand;

  *power = p;
}

void get_normalized_boundaries(double num, diy_fp *minus, diy_fp *plus) {
  diy_fp v = get_diy(num);

  diy_fp plus_res;
  plus_res.f = (v.f << 1) + 1;
  plus_res.e = v.e - 1;

  normalize(&plus_res);

  diy_fp minus_res;
  if ((as_uint64(num) & SIGNIFICAND_MASK) && (v.e != DENORMAL_EXPONENT)) {
    minus_res.f = (v.f << 2) - 1;
    minus_res.e = v.e - 2;
  } else {
    minus_res.f = (v.f << 1) - 1;
    minus_res.e = v.e - 1;
  }

  minus_res.f = minus_res.f << (minus_res.e - plus_res.e);
  minus_res.e = plus_res.e;

  *minus = minus_res;
  *plus = plus_res;
}

void biggest_power_of_ten(uint64_t number, int number_bits, uint64_t *power,
                          int *exponent_plus_one) {
  assert(number < (1u << (number_bits + 1)));

  static unsigned int const k_small_powers_of_ten[] = {
      0,      1,       10,       100,       1000,      10000,
      100000, 1000000, 10000000, 100000000, 1000000000};

  int exponent_plus_one_guess = ((number_bits + 1) * LOG_10_2);
  exponent_plus_one_guess++;

  if (number < k_small_powers_of_ten[exponent_plus_one_guess]) {
    exponent_plus_one_guess--;
  }

  *power = k_small_powers_of_ten[exponent_plus_one_guess];
  *exponent_plus_one = exponent_plus_one_guess;
}

void round_weed(char *buf, int length, uint64_t distance_to_high_w,
                uint64_t unsafe_interval, uint64_t rest, uint64_t ten_kappa,
                uint64_t unit) {
  uint64_t small_distance = distance_to_high_w - unit;
  // uint64_t big_distance = distance_to_high_w + unit;

  assert(rest <= unsafe_interval);

  while (rest < small_distance && unsafe_interval - rest >= ten_kappa &&
         (rest + ten_kappa < small_distance ||
          small_distance - rest >= rest + ten_kappa - small_distance)) {
    buf[length - 1]--;
    rest += ten_kappa;
  }
}

void generate_digits(diy_fp low, diy_fp w, diy_fp high, char *buffer,
                     int *length, int *kappa) {
  assert(low.e == w.e && w.e == high.e);
  assert(low.f + 1 <= high.f - 1);
  assert(MINIMAL_TARGET_EXPONENT <= w.e && w.e <= MAXIMAL_TARGET_EXPONENT);

  uint64_t unit = 1;
  diy_fp too_low = {low.f - unit, low.e};
  diy_fp too_high = {high.f + unit, high.e};

  diy_fp unsafe_interval = minus(too_high, too_low);

  diy_fp one = {(uint64_t)1 << -w.e, w.e};

  uint64_t integrals = too_high.f >> -one.e;
  uint64_t fractionals = too_high.f & (one.f - 1);
  uint64_t divisior;

  int divisior_exponent_plus_one;

  biggest_power_of_ten(integrals, DIY_FP_SAGNIFICAND_SIZE - (-one.e), &divisior,
                       &divisior_exponent_plus_one);

  *kappa = divisior_exponent_plus_one;
  *length = 0;

  while (*kappa > 0) {
    int digit = integrals / divisior;
    assert(digit <= 9);

    buffer[*length] = '0' + digit;
    (*length)++;

    integrals %= divisior;
    (*kappa)--;

    uint64_t rest = ((uint64_t)integrals << -one.e) + fractionals;

    if (rest < unsafe_interval.f) {
      diy_fp temp = minus(too_high, w);
      return round_weed(buffer, *length, temp.f, unsafe_interval.f, rest,
                        (uint64_t)divisior << -one.e, unit);
    }

    divisior /= 10;
  }

  for (;;) {
    fractionals *= 10;
    unit *= 10;
    unsafe_interval.f *= 10;

    int digit = (int)(fractionals >> -one.e);

    assert(digit <= 9);

    buffer[*length] = '0' + digit;
    (*length)++;

    fractionals &= one.f - 1;
    (*kappa)--;

    if (fractionals < unsafe_interval.f) {
      diy_fp temp = minus(too_high, w);
      return round_weed(buffer, *length, temp.f * unit, unsafe_interval.f,
                        fractionals, one.f, unit);
    }
  }
}

void grisu3(double v, char *buf, int *length, int *decimal_exponent) {
  diy_fp w = get_normalized_diy(v);

  diy_fp boundary_minus, boundary_plus;
  get_normalized_boundaries(v, &boundary_minus, &boundary_plus);

  diy_fp ten_mk;
  int mk;

  assert(boundary_minus.e == boundary_plus.e);

  int ten_mk_minimal_binary_exponent =
      MINIMAL_TARGET_EXPONENT - (w.e + DIY_FP_SAGNIFICAND_SIZE);
  int ten_mk_maximal_binary_exponent =
      MAXIMAL_TARGET_EXPONENT - (w.e + DIY_FP_SAGNIFICAND_SIZE);

  get_cached_for_power_for_binary_exponent_range(ten_mk_minimal_binary_exponent,
                                                 ten_mk_maximal_binary_exponent,
                                                 &ten_mk, &mk);

  assert(MINIMAL_TARGET_EXPONENT <= w.e + ten_mk.e + DIY_FP_SAGNIFICAND_SIZE &&
         MAXIMAL_TARGET_EXPONENT >= w.e + ten_mk.e + DIY_FP_SAGNIFICAND_SIZE);

  diy_fp scaled_w = multiply(w, ten_mk);

  assert(scaled_w.e == boundary_plus.e + ten_mk.e + DIY_FP_SAGNIFICAND_SIZE);

  diy_fp scaled_boundary_minus = multiply(boundary_minus, ten_mk);
  diy_fp scaled_boundary_plus = multiply(boundary_plus, ten_mk);

  int kappa;
  generate_digits(scaled_boundary_minus, scaled_w, scaled_boundary_plus, buf,
                  length, &kappa);

  *decimal_exponent = -mk + kappa;
}
