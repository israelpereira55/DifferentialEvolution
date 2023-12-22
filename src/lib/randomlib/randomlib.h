#ifndef RANDOMLIB_H_
#define RANDOMLIB_H_

#include <chrono>
#include <random>

// auto seed =
// std::chrono::high_resolution_clock::now().time_since_epoch().count();

extern std::random_device dev;
extern std::mt19937 rng;
// std::mt19937 rng(42);

// Range is inclusive [lower_bound, upper_bound]
int random_integer(int lower_bound, int upper_bound);
double random_real(double lower_bound, double upper_bound);

extern std::uniform_int_distribution<int> default_distr;

// Range is inclusive [lower_bound, upper_bound]
void rng_define_default_range(int lower_bound, int upper_bound);
int random_integer_default_range();

#endif  // RANDOMLIB_H_
