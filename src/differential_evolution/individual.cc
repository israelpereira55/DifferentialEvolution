#include "individual.h"
#include "src/lib/randomlib/randomlib.h"

void 
Individual::CreateRandom(int lower_bound, int upper_bound, int N) {
    this->phenotype = std::vector<int>(N);
    this->defined = true;

    for(int i = 0; i < N; i++) {
        this->phenotype[i] = random_integer_default_range();
    }
}
