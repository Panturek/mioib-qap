#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

typedef std::vector<int> Permutation;

void printToFile(const std::string filename,
	const std::vector<double> time,
	const double f_time,
	const std::vector<int> costs,
	const std::vector<int> steps,
	const std::vector<Permutation> permutations);

std::vector<int> row_sum(const std::vector<std::vector<int>> matrix);
std::vector<int> col_sum(const std::vector<std::vector<int>> matrix);