#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <vector>

#include "src/lib/randomlib/randomlib.h"

using namespace std;

/* To be consistent, right after creation the individual needs:
 * - calculate cost
 * - check Feasibility
 * - mark defined as true
 */
class Individual {
   private:
   public:
    // vector<double> genotype;  /* continuous space */
    vector<int> phenotype; /* discrete space */

    double cost = 0;
    bool feasible = false;
    bool defined = false;

    // Individual(int N) {
    //   // individual.reserve(N);
    //   individual = vector<int>(N, -1);
    // }
    Individual() = default;
    ~Individual() = default;

    void CreateRandom(const vector<vector<int>>& graph, int lower_bound, int upper_bound, int N);

    void CheckFeasibility();
    void DefineCost(const vector<vector<int>>& graph);
};

#endif  // INDIVIDUAL_H_
