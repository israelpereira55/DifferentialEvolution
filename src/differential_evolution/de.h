#ifndef DE_H_
#define DE_H_

#include <vector>

#include "individual.h"
#include "settings/settings.h"

using namespace std;

typedef struct generation Generation;

struct generation {
    vector<Individual> individuals;
    int best_individual_idx = -1;
};

class DE {
   private:
    int N;                     // * dimension of individuals (number os components)
    int NP;                    // * population size
    double F, CR;              // * F: mutation factor; CR: crossover ratio
    double penalty;            // * penalty is an increase in the individual cost
    int max_generations;       // * maximum number of generations
    int generation_id = 0;     // * generation identifier
    Generation generation;     // * generation of individuals
    DETechnique de_technique;  // * Differential Evolution Technique/Strategy

    bool defined_limits;
    int lower_bound;  // * phenotype space limits
    int upper_bound;  // * phenotype space limits

    bool GetThreeIndividualIndexes(int target_index, enum MutationType mutation_type, int& r1,
                                   int& r2, int& r3);

   public:
    DE(const Settings& settings) {
        N = settings.N;
        NP = settings.NP;
        F = settings.F;
        CR = settings.CR;
        penalty = settings.penalty;
        max_generations = settings.max_generations;
        de_technique = settings.de_technique;

        defined_limits = settings.defined_limits;
        lower_bound = settings.lower_bound;
        upper_bound = settings.upper_bound;
    }
    ~DE() = default;

    Individual Mutation(const Individual& Xr1, const Individual& Xr2, const Individual& Xr3);
    Individual Crossover(const Individual& target, const Individual& mutant);
    Individual Selection(const Individual& target, const Individual& trial);

    Generation InitialGeneration(const vector<vector<int>>& graph);

    Individual DifferentialEvolution(const vector<vector<int>>& graph);
};

#endif  // DE_H_
