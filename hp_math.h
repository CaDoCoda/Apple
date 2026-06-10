#ifndef HP_MATH_H
#define HP_MATH_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

// Define precision (number of decimal digits for printing)
#define HP_PRECISION 100

// Define precision (number of bits for mantissa) for GMP mpf_t
// 100 decimal digits is approximately 100 * log2(10) bits = 100 * 3.3219 = 332 bits.
#define HP_BITS_PRECISION 335

// hp_num will now be a wrapper around mpf_t
typedef mpf_t hp_num;

// Function declarations
void hp_init(hp_num num);
void hp_clear(hp_num num);
void hp_set_str(hp_num num, const char* s);
void hp_set_d(hp_num num, double d);
void hp_get_str(char* str, size_t size, const hp_num num);
void hp_print(const hp_num num);

void hp_add(hp_num rop, const hp_num op1, const hp_num op2);
void hp_sub(hp_num rop, const hp_num op1, const hp_num op2);
void hp_mul(hp_num rop, const hp_num op1, const hp_num op2);
void hp_div(hp_num rop, const hp_num op1, const hp_num op2);
void hp_sqrt(hp_num rop, const hp_num op);
void hp_pow_ui(hp_num rop, const hp_num base, unsigned long int exp);

// Comparison
int hp_cmp(const hp_num op1, const hp_num op2);
int hp_sgn(const hp_num op);

// Transcendental functions
void hp_sin(hp_num rop, const hp_num op);
void hp_asin(hp_num rop, const hp_num op);

// Constants
extern hp_num HP_PI;
extern hp_num HP_PHI;
extern hp_num HP_H;
extern hp_num HP_C;

void hp_init_constants();
void hp_clear_constants();

#endif // HP_MATH_H
