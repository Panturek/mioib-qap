#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

std::vector<int> permutacja(unsigned const int & n)
{
	std::vector<int> arr(n);
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

void readData(const std::string filename,
	std::vector< std::vector<int> >& facilities,
	std::vector< std::vector<int> >& locations)
{
	std::ifstream data;
	data.open(filename);

	int dimension;
	data >> dimension;

	for (int i = 0; i < dimension; i++) {
		facilities.push_back(std::vector<int>());
		for (int i = 0; i < dimension; i++)
		{
			int number;
			data >> number;
			facilities.back().push_back(number);
		}
	}

	for (int i = 0; i < dimension; i++) {
		locations.push_back(std::vector<int>());
		for (int i = 0; i < dimension; i++)
		{
			int number;
			data >> number;
			locations.back().push_back(number);
		}
	}

	data.close();
}

int getCost(std::vector<int> &perm, std::vector< std::vector<int> > &P, std::vector< std::vector<int> > &L)
{
	int cost = 0;
	for (int i = 0; i < perm.size(); i++)
	{
		for (int j = 0; j < perm.size(); j++)
		{
			cost += P[i][j] * L[perm[i] - 1][perm[j] - 1];
		}
	}
	return cost;
}

int main()
{
	srand(time(NULL));
	//std::vector<int> all = permutacja(26);
	std::vector<int> all = { 11, 15,  26,   7,   4,  13,  12,   2,   6,  18,   9,   5,   1,  21,   8,
		14,   3,  20,  19,  10,  17,  25,  16,  24,  22,  23 };

	std::vector<std::vector<int>> facilities;
	std::vector<std::vector<int>> locations;
	readData("data/bur26a.dat", facilities, locations);
	int cost = getCost(all, facilities, locations);
	std::cout << cost;
	getchar();
	return 0;
}
