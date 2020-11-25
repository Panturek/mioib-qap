#include "utils.hpp"

void printToFile(const std::string filename,
	const std::vector<double> time,
	const double f_time,
	const std::vector<int> costs,
	const std::vector<int> steps,
	const std::vector<Permutation> permutations)
{
	std::ofstream output;
	output.open(filename);
	for (int i = 0; i < costs.size(); i++)
	{
		output << costs[i] << ",\t"
			<< time[i] << ",\t"
			<< f_time << ",\t"
			<< steps[i] << ",\t";
		for (auto&& n : permutations[i]) {
			output << n << " ";
		}
		output << "\n";
	}
	output.close();
}

void randomPrintToFile(const std::string filename,
	const std::vector<int> costs,
	const std::vector<int> steps,
	const std::vector<Permutation> permutations)
{
	std::ofstream output;
	output.open(filename);
	for (int i = 0; i < costs.size(); i++)
	{
		output << costs[i] << ",\t"
			<< steps[i] << ",\t";
		for (auto&& n : permutations[i]) {
			output << n << " ";
		}
		output << "\n";
	}
	output.close();
}

void heuristicsPrintToFile(const std::string filename,
	const double f_time,
	const int cost,
	const Permutation permutation)
{
	std::ofstream output;
	output.open(filename);

	output << cost << ",\t"
		<< f_time << ",\t";
	for (auto&& n : permutation) {
		output << n << " ";
	}
	output << "\n";

	output.close();
}

std::vector<int> row_sum(const std::vector<std::vector<int>> matrix) {
	std::vector<int> result;
	for (int i = 0; i < matrix.size(); i++)
	{
		auto row = matrix[i];
		int row_sum = std::accumulate(row.begin(), row.end(), 0);
		result.push_back(row_sum);
	}

	return result;
}

std::vector<int> col_sum(const std::vector<std::vector<int>> matrix) {
	auto dim = matrix.size();
	std::vector<int>result(dim, 0);

	for (int i = 0; i < dim; i++)
	{
		auto row = matrix[i];

		for (int j = 0; j < dim; j++)
		{
			result[j] += row[j];
		}
	}

	return result;
}