#ifndef SETTINGS_H_
#define SETTINGS_H_

enum MutationType { MUTATION_RAND, MUTATION_BEST };
enum CrossoverType { CROSSOVER_BIN, CROSSOVER_EXP };
enum DETechnique { RAND_1_BIN, RAND_1_EXP, BEST_1_BIN, BEST_1_EXP };

// typedef struct settings Settings;

// struct settings{
//   int NP;
//   double F, CR;
//   double penalty;
//   int max_generations;
//   enum DETechnique de_technique;
// };

class Settings {
   public:
    int N;
    int NP;
    double F, CR;
    double penalty;
    int max_generations;
    enum DETechnique de_technique;

    bool defined_limits;
    int lower_bound;
    int upper_bound;

    Settings() = default;
    ~Settings() = default;
};

#endif  // SETTINGS_H_
