#include "randomlib.h"

// https://stackoverflow.com/questions/60454047/how-to-seed-a-random-number-generator-in-a-safe-and-portable-way
// https://stackoverflow.com/questions/34490599/c11-how-to-set-seed-using-random

std::random_device rd;
std::mt19937 rng(rd());

// Range: [lower_bound, upper_bound]
int random_integer(int lower_bound, int upper_bound) { 
    std::uniform_int_distribution<int> distr(lower_bound, upper_bound);
    return distr(rng);
}

// Range: [lower_bound, upper_bound)
double random_real(double lower_bound, double upper_bound) { 
    std::uniform_real_distribution<double> distr(lower_bound, upper_bound);
    return distr(rng);
}


std::uniform_int_distribution<int> default_distr;

// Range is inclusive [lower_bound, upper_bound]
void rng_define_default_range(int lower_bound, int upper_bound) {
  default_distr = std::uniform_int_distribution<int>(lower_bound, upper_bound);
}

int random_integer_default_range() {
  return default_distr(rng);
}
