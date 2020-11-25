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


int QAP::updateCost(const Permutation& old_perm, const Permutation& new_perm, unsigned const int& i, unsigned const int& j)
{
	int new_cost = cost;
	
	int dim = old_perm.size();
	
	for (int idx = 0; idx < dim; idx++)
	{

		if (idx == i)
		{
			new_cost -= facilities[i][idx] * locations[old_perm[i]][old_perm[idx]];
			new_cost += facilities[i][idx] * locations[new_perm[i]][new_perm[idx]];

			new_cost -= facilities[j][idx] * locations[old_perm[j]][old_perm[idx]];
			new_cost += facilities[j][idx] * locations[new_perm[j]][new_perm[idx]];

			new_cost -= facilities[idx][j] * locations[old_perm[idx]][old_perm[j]];
			new_cost += facilities[idx][j] * locations[new_perm[idx]][new_perm[j]];

			continue;
		}

		if (idx == j)
		{
			new_cost -= facilities[idx][j] * locations[old_perm[idx]][old_perm[j]];
			new_cost += facilities[idx][j] * locations[new_perm[idx]][new_perm[j]];

			continue;
		}

		new_cost -= facilities[i][idx] * locations[old_perm[i]][old_perm[idx]];
		new_cost += facilities[i][idx] * locations[new_perm[i]][new_perm[idx]];

		new_cost -= facilities[j][idx] * locations[old_perm[j]][old_perm[idx]];
		new_cost += facilities[j][idx] * locations[new_perm[j]][new_perm[idx]];

		new_cost -= facilities[idx][i] * locations[old_perm[idx]][old_perm[i]];
		new_cost += facilities[idx][i] * locations[new_perm[idx]][new_perm[i]];

		new_cost -= facilities[idx][j] * locations[old_perm[idx]][old_perm[j]];
		new_cost += facilities[idx][j] * locations[new_perm[idx]][new_perm[j]];
	}
	return new_cost;

}

std::pair<Permutation, int> QAP::randomSearch(unsigned const int &n, const double &time_seconds)
{
	int steps = 0;
	Permutation act = generatePermutation(n);

	clock_t begin = clock();

	do
	{
		act = generatePermutation(n);
		steps++;

	} while (double(clock() - begin) / CLOCKS_PER_SEC < time_seconds);

	return std::make_pair(act, steps);
}

std::pair<Permutation, int> QAP::randomWalk(unsigned const int &n, const double &time_seconds)
{
	int steps = 0;
	Permutation act = generatePermutation(n);

	clock_t begin = clock();

	do
	{
		int random_i = std::rand() % (n - 1);
		int random_j = (std::rand() % (n - random_i - 1)) + random_i + 1;

		std::swap(act[random_i], act[random_j]);
		steps++;
	} while (double(clock() - begin) / CLOCKS_PER_SEC < time_seconds);

	return std::make_pair(act, steps);
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
	
	Permutation best_perm = act;
	int best_cost = cost;

	do
	{
		cost = best_cost;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				Permutation y = act;
				std::swap(y[i], y[j]);

				int new_cost = updateCost(act, y, i, j);
				if (new_cost < best_cost)
				{
					best_perm = y;
					best_cost = new_cost;
				}
			}
		}
		act = best_perm;
		steps++;
	} while (best_cost != cost);

	return std::make_pair(act, steps);
}



std::pair<Permutation, int> QAP::heuristics(unsigned const int &n)
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

	return std::make_pair(solution, 0);
}