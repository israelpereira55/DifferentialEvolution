#include "de.h"

#include "src/lib/randomlib/randomlib.h"

Individual
DE::Mutation(const Individual& Xr1, const Individual& Xr2, const Individual& Xr3) { 
    Individual mutant;
    mutant.defined = true;

    for (int i = 0; i < this->N; i++) {
        mutant.phenotype[i] = Xr1.phenotype[i] - this->F *(Xr2.phenotype[i] - Xr3.phenotype[i]) + 0.5;

        if (mutant.phenotype[i] < this->lower_bound or mutant.phenotype[i] > this->upper_bound) { // range: [1, color_num]
            mutant.phenotype[i] = random_integer(this->lower_bound, this->upper_bound);
        }
    }

    return mutant;
}


Individual 
DE::Crossover(const Individual target, const Individual& mutant) {
    Individual trial;
    trial.defined = true;

    for (int i = 0; i < this->N; i++) {
        if (random_real(0., 1.) <= this->CR) {
            trial.phenotype[i] = mutant.phenotype[i];
        } else {
            trial.phenotype[i] = target.phenotype[i];
        }
    }

    int j = random_integer(0,this->N -1);
    trial.phenotype[j] = mutant.phenotype[j];

    return trial;
}

bool 
DE::GetThreeIndividualIndexes(int target_idx, enum MutationType mutation_type, int& r1, int& r2, int& r3) {
    // Best individual should be always defined (the best feasible solution, otherwise, if no feasible 
    // solution exists, then it is the lowest cost individual)
    // Also, in mutation best, r1 can be the target.
    if (mutation_type != MUTATION_BEST) {
        do { r1 = random_integer(0, this->NP-1); } while(r1 == target_idx);
    } else {
        r1 = this->best_individual_idx;
    }
    
    do { r2 = random_integer(0, this->NP-1); } while(r2 == target_idx || r2 == r1);
    do { r3 = random_integer(0, this->NP-1); } while(r3 == target_idx || r3 == r2 || r3 == r1);

    return true;
}


vector<Individual>
DE::InitialGeneration() {
    vector<Individual> generation(this->NP);

    for (int i = 0; i < this->NP; i++) {
        generation[i].CreateRandom(this->lower_bound, this->upper_bound, this->N);
    }

    return generation;
}


vector<Individual> 
DE::NewGeneration() {
    vector<Individual> new_generation(this->NP);

    for (int target_idx = 0; target_idx < this->NP; target_idx++) {

    }


    return new_generation;
}


Individual
DifferentialEvolution() {
    vector<Individual> generation = InitialGeneration();
    Individual best_solution = generation.best_solution;

    int gen_id = 0;
    do {
        gen_id += 1;
        
        vector<Individual> new_generation = vector<Individual>(this->NP);
        new_generation.best_solution = generation.best_solution;
        new_generation.individuals[0] = generation.individuals[0];

        for(target_idx = 0; target_idx < this->NP; target_idx++) {
            int r1, r2, r3;
            GetThreeIndividualIndexes(target_idx, mutation_type, r1, r2, r3);

            Individual mutant = Mutation(generation.individuals[r1], generation.individuals[r2], generation.individuals[r3]);
            Individual trial  = Crossover(generation.individuals[target_idx], mutant);

            if (trial.cost < generation.individuals[target_idx].cost) {
                new_generation[target_idx] = selected_individual;

                if (trial.cost < new_generation.best_solution) {
                    new_generation.best_solution = trial;
                }

            } else {
                new_generation[target_idx] = generation.individuals[target_idx];
            }
            
    } while(gen_id < this->max_generations);

    return best_solution;
}