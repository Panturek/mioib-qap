#include "qap.hpp"
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

Permutation QAP::generatePermutation(unsigned const int & n)
{
	Permutation arr(n);
	std::iota(arr.begin(), arr.end(), 0);

	for (int i = 0; i < n; i++)
	{
		int random = std::rand() % (n - i);
		int hold = arr[random];
		arr.erase(arr.begin() + random);
		arr.push_back(hold);
	}
	return arr;
}

void QAP::readData(const std::string filename)
{
	std::ifstream data;
	data.open(filename);

	int dimension;
	data >> dimension;

	for (int i = 0; i < dimension; i++) {
		facilities.push_back(Permutation());
		for (int i = 0; i < dimension; i++)
		{
			int number;
			data >> number;
			facilities.back().push_back(number);
		}
	}

	for (int i = 0; i < dimension; i++) {
		locations.push_back(Permutation());
		for (int i = 0; i < dimension; i++)
		{
			int number;
			data >> number;
			locations.back().push_back(number);
		}
	}
	data.close();
}

int QAP::getCost(const Permutation &perm)
{
	int cost = 0;
	for (int i = 0; i < perm.size(); i++)
	{
		for (int j = 0; j < perm.size(); j++)
		{
			cost += facilities[i][j] * locations[perm[i]][perm[j]];
		}
	}
	return cost;
}


int QAP::updateCost(const Permutation& old_perm, const Permutation& new_perm, const int& i, const int& j)
{
	int new_cost = cost;
	new_cost -= facilities[i][j] * locations[old_perm[i]][old_perm[j]];
	new_cost += facilities[i][j] * locations[new_perm[i]][new_perm[j]];
	return new_cost;
}

Permutation QAP::randomSearch(unsigned const int &n, const double &time_seconds)
{
	Permutation act = generatePermutation(n);

	clock_t begin = clock();

	do
	{
		act = generatePermutation(n);

	} while (double(clock() - begin) / CLOCKS_PER_SEC < time_seconds);

	return act;
}

Permutation QAP::randomWalk(unsigned const int &n, const double &time_seconds)
{
	Permutation act = generatePermutation(n);

	clock_t begin = clock();

	do
	{
		int random_i = std::rand() % (n - 1);
		int random_j = (std::rand() % (n - random_i - 1)) + random_i + 1;

		std::swap(act[random_i], act[random_j]);
	} while (double(clock() - begin) / CLOCKS_PER_SEC < time_seconds);

	return act;
}

std::pair<Permutation, int> QAP::localGreedy(unsigned const int &n)
{
	int steps = 0;
	Permutation act = generatePermutation(n);
	cost = getCost(act);
	bool found = false;
	int init_cost;

	do
	{
		init_cost = cost;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				Permutation y(act);
				std::swap(y[i], y[j]);

				int new_cost = updateCost(act, y, i, j);
				if (new_cost < cost)
				{
					act = y;
					cost = new_cost;
					found = true;
					steps++;
					break;
				}
			}
			if (found == true)
			{
				break;
			}
		}
		found = false;
	} while (init_cost != cost);

	return std::make_pair(act, steps);
}

std::pair<Permutation, int> QAP::localSteepest(unsigned const int &n)
{
	int steps = 0;
	Permutation act = generatePermutation(n);
	cost = getCost(act);
	int init_cost;

	bool finish = false;

	do
	{
		init_cost = cost;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				Permutation y(act);
				std::swap(y[i], y[j]);

				int new_cost = updateCost(act, y, i, j);
				if (new_cost < cost)
				{
					act = y;
					cost = new_cost;
					steps++;
				}
			}
		}
	} while (init_cost != cost);

	return std::make_pair(act, steps);
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

Permutation QAP::heuristics(unsigned const int &n)
{
	std::vector<Permutation> P = facilities;
	std::vector<Permutation> L = locations;

	Permutation solution(n);

	auto cols = col_sum(L);
	auto rows = row_sum(P);

	for (int i = 0; i < n; i++)
	{
		auto max_row = std::distance(rows.begin(), std::max_element(rows.begin(), rows.end()));
		auto min_col = std::distance(cols.begin(), std::min_element(cols.begin(), cols.end()));

		solution[max_row] = min_col;

		cols[min_col] = INT_MAX;
		rows[max_row] = INT_MIN;
	}

	return solution;
}