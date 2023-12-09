#ifndef DE_H_
#define DE_H_

#include <vector>

#include "individual.h"
#include "settings/settings.h"

using namespace std;

class DE {
  private:
    int N;                      // * dimension of individuals (number os components)
    int NP;                     // * population size 
    double F, CR;               // * F: mutation factor; CR: crossover ratio
    double penalty;             // * penalty is an increase in the individual cost
    int max_generations;        // * maximum number of generations
    int generation_id = 0;      // * generation identifier
    DETechnique de_technique;   // * Differential Evolution Technique/Strategy

    int best_individual_idx = -1; //put best solution os position 0?
    vector<Individual> generation;

    bool defined_limits;
    int lower_bound;             // * phenotype space limits
    int upper_bound;             // * phenotype space limits

    bool GetThreeIndividualIndexes(int target_index, enum MutationType mutation_type, int& r1, int& r2, int& r3);


  public:
    DE(const Settings& settings){
      N = settings.N;
      NP = settings.NP;
      N = settings.N;
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

    Individual Mutation(const Individual& Xr1, const Individual& Xr2, const Individual& Xr3, int color_num);
    Individual Crossover(const Individual target, const Individual& mutant);
    Individual Selection(const Individual& target, const Individual& trial);

    vector<Individual> InitialGeneration(int lower_bound, int upper_bound);
    vector<Individual> NewGeneration();
};

#endif  // DE_H_
