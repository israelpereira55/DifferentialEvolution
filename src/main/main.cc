/**
 * Simple Combinatorial Differential Evolution (SC-DE)
 *
 * A simple Addaptation Differential Evolution by Storn and Price.
 *
 */
#include <fstream>
#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "glog/logging.h"
#include "glog/stl_logging.h"
#include "src/differential_evolution/de.h"
#include "src/lib/randomlib/randomlib.h"
#include "yaml-cpp/yaml.h"

using namespace std;

ABSL_FLAG(bool, log, false, "Enable logging");
ABSL_FLAG(bool, verbose, false, "Enable verbose mode");
ABSL_FLAG(int, k, 0, "Graph chromatic number");
ABSL_FLAG(std::string, instance, "", "Instance filename");

// If the instance has 125 nodes [1-125],
// in the program it will be node 0-124, but should be presented as [1-125].
vector<vector<int>> read_instance(std::string filename, bool verbose = false) {
    ifstream instance_file(filename);

    if (!instance_file.is_open()) {
        LOG(FATAL) << "Could not open file: " << filename;
        exit(1);
    }

    vector<vector<int>> graph;
    int edges_num = 0;
    int nodes_num = 0;
    string format;

    char c;
    std::string line;
    while (instance_file >> c) {
        switch (c) {
            case 'c':
                std::getline(instance_file, line);
                if (verbose) std::cout << "c" << line << std::endl;
                break;

            case 'p':
                instance_file >> format >> nodes_num >> edges_num;
                graph = vector<vector<int>>(nodes_num, vector<int>());
                if (verbose) {
                    std::cout << "p " << format << " " << nodes_num << " " << edges_num
                              << std::endl;
                }
                break;

            case 'e':
                int v1, v2;
                instance_file >> v1 >> v2;
                graph[v1 - 1].push_back(v2 - 1);
                if (verbose) std::cout << "e " << v1 << " " << v2 << std::endl;
                break;

            default:
                LOG(FATAL) << "Bad instance";
                exit(1);
        }
    }

    return graph;
}

Settings parse_settings(string filename) {
    Settings settings{};

    try {
        YAML::Node config = YAML::LoadFile(filename);

        auto DE = config["DE"];

        settings.NP = DE["NP"].as<int>();
        settings.F = DE["F"].as<double>();
        settings.CR = DE["CR"].as<double>();
        // std::string estrategia_char_TODO = DE["Technique"].as<string>();
        settings.de_technique = RAND_1_BIN;
        settings.max_generations = DE["MaxGenerations"].as<int>();

    } catch (const YAML::BadFile& e) {
        LOG(FATAL) << "Bad settings: " << e.msg;
        exit(1);
    } catch (const YAML::ParserException& e) {
        LOG(FATAL) << "Bad settings: " << e.msg;
        exit(1);
    }

    return settings;
}

void print_solution(const Individual& individual, string filename) {
    ofstream file;
    file.open(filename);

    if (individual.feasible) {
        file << "# feasible solution\n";
    } else {
        file << "# infeasible solution\n";
    }

    int N = individual.phenotype.size();
    for (int i = 0; i < N; i++) {
        file << i + 1 << " " << individual.phenotype[i] << "\n";
    }

    file.close();
}

void configure_by_graph(const vector<vector<int>>& graph, Settings& settings, int lower_bound,
                        int upper_bound) {
    settings.N = graph.size();
    settings.lower_bound = 1;
    settings.upper_bound = upper_bound;
    settings.defined_limits = true;
}

// LOG(INFO) << "ABC, it's easy as " << 10;
// LOG(WARNING) << "This is a warning message";
// LOG(ERROR) << "This is an error message";
// LOG(FATAL) << "This is a fatal message";
// CHECK(5 == 4) << "Check failed!";

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_alsologtostderr = true;  // Log both to log file and stderr

    absl::SetProgramUsageMessage("--message: Simple Combinatorial Differential Evolution (SC-DE)");
    absl::ParseCommandLine(argc, argv);

    if (absl::GetFlag(FLAGS_instance) == "") {
        std::cout << "Please specify the instance file.\n" << "Aborting..." << std::endl;
        exit(0);
    }

    // Temporary
    if (absl::GetFlag(FLAGS_k) == 0) {
        std::cout << "Please specify the instance chromatic number.\n"
                  << "Aborting..." << std::endl;
        exit(0);
    }

    rng_define_default_range(1, 32);

    vector<vector<int>> graph =
        read_instance(absl::GetFlag(FLAGS_instance), absl::GetFlag(FLAGS_verbose));
    Settings settings = parse_settings("settings/settings.yaml");

    int lower_bound = 1;
    int upper_bound = absl::GetFlag(FLAGS_k);
    configure_by_graph(graph, settings, lower_bound, upper_bound);

    DE metaheuristic = DE(settings);
    Individual best_solution = metaheuristic.DifferentialEvolution(graph);

    if (best_solution.feasible) {
        std::cout << "Feasible solution." << std::endl;
    } else {
        std::cout << "Infeasible solution.\n"
                  << "Conflict number on the best solution: " << best_solution.cost << std::endl;
    }

    print_solution(best_solution, "solution.txt");

    return 0;
}