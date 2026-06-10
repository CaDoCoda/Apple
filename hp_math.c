#include "hp_math.h"
#include <string.h>

// Global constants
hp_num HP_PI;
hp_num HP_PHI;
hp_num HP_H;
hp_num HP_C;

// --- Static Helper Functions for Internal Use ---

static void hp_factorial(hp_num rop, unsigned int n) {
    mpf_set_ui(rop, 1);
    for (unsigned int i = 2; i <= n; ++i) {
        mpf_mul_ui(rop, rop, i);
    }
}

static void hp_fmod(hp_num rop, const hp_num num, const hp_num den) {
    hp_num quotient, temp_mul;
    mpf_init2(quotient, HP_BITS_PRECISION);
    mpf_init2(temp_mul, HP_BITS_PRECISION);

    mpf_div(quotient, num, den);
    mpf_floor(quotient, quotient);
    mpf_mul(temp_mul, quotient, den);
    mpf_sub(rop, num, temp_mul);

    mpf_clear(quotient);
    mpf_clear(temp_mul);
}

// --- Public API Functions ---

void hp_init(hp_num num) {
    mpf_init2(num, HP_BITS_PRECISION);
}

void hp_clear(hp_num num) {
    mpf_clear(num);
}

void hp_set_str(hp_num num, const char* s) {
    mpf_set_str(num, s, 10);
}

void hp_set_d(hp_num num, double d) {
    mpf_set_d(num, d);
}

void hp_get_str(char* str, size_t size, const hp_num num) {
    mpf_get_str(str, NULL, 10, HP_PRECISION, num);
}

void hp_print(const hp_num num) {
    mpf_out_str(stdout, 10, HP_PRECISION, num);
    printf("\n");
}

void hp_add(hp_num rop, const hp_num op1, const hp_num op2) {
    mpf_add(rop, op1, op2);
}

void hp_sub(hp_num rop, const hp_num op1, const hp_num op2) {
    mpf_sub(rop, op1, op2);
}

void hp_mul(hp_num rop, const hp_num op1, const hp_num op2) {
    mpf_mul(rop, op1, op2);
}

void hp_div(hp_num rop, const hp_num op1, const hp_num op2) {
    mpf_div(rop, op1, op2);
}

void hp_sqrt(hp_num rop, const hp_num op) {
    mpf_sqrt(rop, op);
}

void hp_pow_ui(hp_num rop, const hp_num base, unsigned long int exp) {
    mpf_pow_ui(rop, base, exp);
}

int hp_cmp(const hp_num op1, const hp_num op2) {
    return mpf_cmp(op1, op2);
}

int hp_sgn(const hp_num op) {
    return mpf_sgn(op);
}

// --- Transcendental functions (Taylor series implementations using GMP) ---

void hp_sin(hp_num rop, const hp_num op) {
    hp_num term, x_sq, two_pi, x_reduced, current_x_pow, factorial_val, epsilon, abs_term;
    mpf_init2(term, HP_BITS_PRECISION);
    mpf_init2(x_sq, HP_BITS_PRECISION);
    mpf_init2(two_pi, HP_BITS_PRECISION);
    mpf_init2(x_reduced, HP_BITS_PRECISION);
    mpf_init2(current_x_pow, HP_BITS_PRECISION);
    mpf_init2(factorial_val, HP_BITS_PRECISION);
    mpf_init2(epsilon, HP_BITS_PRECISION);
    mpf_init2(abs_term, HP_BITS_PRECISION);

    mpf_mul_ui(two_pi, HP_PI, 2);
    hp_fmod(x_reduced, op, two_pi);

    mpf_set(rop, x_reduced);
    mpf_mul(x_sq, x_reduced, x_reduced);
    mpf_set(current_x_pow, x_reduced);
    mpf_set_str(epsilon, "1e-105", 10);

    for (unsigned int i = 1; i < 100; ++i) {
        mpf_mul(current_x_pow, current_x_pow, x_sq);
        hp_factorial(factorial_val, 2 * i + 1);
        mpf_div(term, current_x_pow, factorial_val);

        if (i % 2 == 1) mpf_sub(rop, rop, term);
        else mpf_add(rop, rop, term);

        mpf_abs(abs_term, term);
        if (mpf_cmp(abs_term, epsilon) < 0) break;
    }

    mpf_clear(term); mpf_clear(x_sq); mpf_clear(two_pi); mpf_clear(x_reduced);
    mpf_clear(current_x_pow); mpf_clear(factorial_val); mpf_clear(epsilon); mpf_clear(abs_term);
}

void hp_asin(hp_num rop, const hp_num op) {
    hp_num term, x_sq, current_x_pow, prev_term_coeff, factor_num, factor_den, factor, two_n_plus_one_val, term_coeff_div_denom, epsilon, abs_term;
    mpf_init2(term, HP_BITS_PRECISION);
    mpf_init2(x_sq, HP_BITS_PRECISION);
    mpf_init2(current_x_pow, HP_BITS_PRECISION);
    mpf_init2(prev_term_coeff, HP_BITS_PRECISION);
    mpf_init2(factor_num, HP_BITS_PRECISION);
    mpf_init2(factor_den, HP_BITS_PRECISION);
    mpf_init2(factor, HP_BITS_PRECISION);
    mpf_init2(two_n_plus_one_val, HP_BITS_PRECISION);
    mpf_init2(term_coeff_div_denom, HP_BITS_PRECISION);
    mpf_init2(epsilon, HP_BITS_PRECISION);
    mpf_init2(abs_term, HP_BITS_PRECISION);

    mpf_set(rop, op);
    mpf_mul(x_sq, op, op);
    mpf_set(current_x_pow, op);
    mpf_set_ui(prev_term_coeff, 1);
    mpf_set_str(epsilon, "1e-105", 10);

    for (unsigned int n = 1; n < 200; ++n) {
        mpf_mul(current_x_pow, current_x_pow, x_sq);
        mpf_set_ui(factor_num, 2 * n - 1);
        mpf_set_ui(factor_den, 2 * n);
        mpf_div(factor, factor_num, factor_den);
        mpf_mul(prev_term_coeff, prev_term_coeff, factor);

        mpf_set_ui(two_n_plus_one_val, 2 * n + 1);
        mpf_div(term_coeff_div_denom, prev_term_coeff, two_n_plus_one_val);
        mpf_mul(term, term_coeff_div_denom, current_x_pow);
        mpf_add(rop, rop, term);

        mpf_abs(abs_term, term);
        if (mpf_cmp(abs_term, epsilon) < 0) break;
    }

    mpf_clear(term); mpf_clear(x_sq); mpf_clear(current_x_pow); mpf_clear(prev_term_coeff);
    mpf_clear(factor_num); mpf_clear(factor_den); mpf_clear(factor);
    mpf_clear(two_n_plus_one_val); mpf_clear(term_coeff_div_denom); mpf_clear(epsilon); mpf_clear(abs_term);
}

void hp_init_constants() {
    mpf_init2(HP_PI, HP_BITS_PRECISION);
    mpf_set_str(HP_PI, "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679", 10);

    mpf_init2(HP_PHI, HP_BITS_PRECISION);
    hp_num five, sqrt_five, one, two;
    mpf_init2(five, HP_BITS_PRECISION); mpf_init2(sqrt_five, HP_BITS_PRECISION);
    mpf_init2(one, HP_BITS_PRECISION); mpf_init2(two, HP_BITS_PRECISION);
    mpf_set_str(five, "5", 10);
    mpf_sqrt(sqrt_five, five);
    mpf_set_str(one, "1", 10);
    mpf_set_str(two, "2", 10);
    mpf_add(HP_PHI, one, sqrt_five);
    mpf_div(HP_PHI, HP_PHI, two);
    mpf_clear(five); mpf_clear(sqrt_five); mpf_clear(one); mpf_clear(two);

    mpf_init2(HP_H, HP_BITS_PRECISION);
    mpf_set_str(HP_H, "6.62607015e-34", 10);

    mpf_init2(HP_C, HP_BITS_PRECISION);
    mpf_set_str(HP_C, "299792458", 10);
}

void hp_clear_constants() {
    mpf_clear(HP_PI);
    mpf_clear(HP_PHI);
    mpf_clear(HP_H);
    mpf_clear(HP_C);
}
