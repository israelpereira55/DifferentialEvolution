#include "de.h"

#include <iostream>

#include "glog/logging.h"
#include "glog/stl_logging.h"
#include "src/lib/randomlib/randomlib.h"

Individual DE::Mutation(const Individual& Xr1, const Individual& Xr2, const Individual& Xr3) {
    Individual mutant;
    mutant.defined = true;
    mutant.phenotype = std::vector<int>(N);

    for (int i = 0; i < this->N; i++) {
        mutant.phenotype[i] =
            Xr1.phenotype[i] - this->F * (Xr2.phenotype[i] - Xr3.phenotype[i]) + 0.5;

        if (mutant.phenotype[i] < this->lower_bound or
            mutant.phenotype[i] > this->upper_bound) {  // range: [1, color_num]
            mutant.phenotype[i] = random_integer(this->lower_bound, this->upper_bound);
        }
    }

    return mutant;
}

Individual DE::Crossover(const Individual& target, const Individual& mutant) {
    Individual trial;
    trial.defined = true;
    trial.phenotype = std::vector<int>(N);

    for (int i = 0; i < this->N; i++) {
        if (random_real(0., 1.) <= this->CR) {
            trial.phenotype[i] = mutant.phenotype[i];
        } else {
            trial.phenotype[i] = target.phenotype[i];
        }
    }

    int j = random_integer(0, this->N - 1);
    trial.phenotype[j] = mutant.phenotype[j];

    return trial;
}

bool DE::GetThreeIndividualIndexes(int target_idx, enum MutationType mutation_type, int& r1,
                                   int& r2, int& r3) {
    // Best individual should be always defined (the best feasible solution, otherwise, if no
    // feasible solution exists, then it is the lowest cost individual) Also, in mutation best, r1
    // can be the target.
    if (mutation_type != MUTATION_BEST) {
        do {
            r1 = random_integer(0, this->NP - 1);
        } while (r1 == target_idx);
    } else {
        r1 = this->generation.best_individual_idx;
    }

    do {
        r2 = random_integer(0, this->NP - 1);
    } while (r2 == target_idx || r2 == r1);
    do {
        r3 = random_integer(0, this->NP - 1);
    } while (r3 == target_idx || r3 == r2 || r3 == r1);

    return true;
}

Generation DE::InitialGeneration(const vector<vector<int>>& graph) {
    Generation generation;

    generation.individuals = vector<Individual>(this->NP);
    double best_cost = 100000;  // TODO int max or do while
    int best_individual_idx = -1;
    for (int i = 0; i < this->NP; i++) {
        generation.individuals[i].CreateRandom(graph, this->lower_bound, this->upper_bound,
                                               this->N);

        if (generation.individuals[i].cost < best_cost) {
            best_individual_idx = i;
            best_cost = generation.individuals[i].cost;
        }
    }

    generation.best_individual_idx = best_individual_idx;

    return generation;
}

Individual DE::DifferentialEvolution(const vector<vector<int>>& graph) {
    Generation generation = InitialGeneration(graph);
    Individual best_solution = generation.individuals[generation.best_individual_idx];

    enum MutationType mutation_type;
    switch (this->de_technique) {
        case RAND_1_BIN:
        case RAND_1_EXP:
            mutation_type = MUTATION_RAND;
            break;

        case BEST_1_BIN:
        case BEST_1_EXP:
            mutation_type = MUTATION_BEST;
            break;

        default:
            LOG(ERROR) << "Bad DE Technique.";
            exit(1);
    }

    int gen_id = 0;
    do {
        gen_id += 1;

        Generation new_generation;
        new_generation.individuals = vector<Individual>(this->NP);
        new_generation.individuals[0] = best_solution;
        new_generation.best_individual_idx = 0;

        for (int target_idx = 0; target_idx < this->NP; target_idx++) {
            int r1, r2, r3;
            GetThreeIndividualIndexes(target_idx, mutation_type, r1, r2, r3);

            Individual mutant = Mutation(generation.individuals[r1], generation.individuals[r2],
                                         generation.individuals[r3]);
            Individual trial = Crossover(generation.individuals[target_idx], mutant);

            trial.DefineCost(graph);

            if (trial.cost < generation.individuals[target_idx].cost) {
                new_generation.individuals[target_idx] = trial;

                if (trial.cost < best_solution.cost) {
                    new_generation.best_individual_idx = target_idx;
                    best_solution = trial;
                }

            } else {
                new_generation.individuals[target_idx] = generation.individuals[target_idx];
            }
        }

        std::cout << "INFO: GEN ID " << gen_id << std::endl;
        std::cout << "INFO: COST " << best_solution.cost << std::endl;

    } while (gen_id < this->max_generations && best_solution.cost > 0);

    return best_solution;
}