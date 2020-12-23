#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

enum Algorithm
{
	randomSearch, randomWalk, localSteepest, localGreedy, heuristics, simmulatedAnnealing, tabu
};

typedef std::vector<int> Permutation;

void printToFile(const std::string filename,
	const std::vector<double> time,
	const double f_time,
	const std::vector<int> costs,
	const std::vector<int> steps,
	const std::vector<int> starting_costs,
	const std::vector<Permutation> permutations);

void randomPrintToFile(const std::string filename,
	const std::vector<int> costs,
	const std::vector<int> steps,
	const double f_time,
	const std::vector<Permutation> permutations);

void heuristicsPrintToFile(const std::string filename,
	const double f_time,
	const int cost,
	const Permutation permutation);

std::vector<int> row_sum(const std::vector<std::vector<int>> matrix);
std::vector<int> col_sum(const std::vector<std::vector<int>> matrix);
