#include "individual.h"

#include "src/lib/randomlib/randomlib.h"

void Individual::CreateRandom(const vector<vector<int>>& graph, int lower_bound, int upper_bound,
                              int N) {
    this->phenotype = std::vector<int>(N);
    this->defined = true;

    for (int i = 0; i < N; i++) {
        // this->phenotype[i] = random_integer_default_range();
        this->phenotype[i] = random_integer(lower_bound, upper_bound);
    }

    DefineCost(graph);
}

void Individual::DefineCost(const vector<vector<int>>& graph) {
    int conflict_num = 0;
    for (unsigned int i = 0; i < graph.size(); i++) {
        for (unsigned int j = 0; j < graph[i].size(); j++) {
            int v1 = i;
            int v2 = graph[i][j];

            if (this->phenotype[v1] == this->phenotype[v2]) {
                conflict_num += 1;
            }
        }
    }

    this->cost = conflict_num;
    if (conflict_num == 0) {
        this->feasible = true;
    }
}
