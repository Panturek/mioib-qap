#include <string>
#include <vector>
#include "utils.hpp"

class QAP{
	unsigned int cost;

public:
	std::vector<Permutation> facilities;
	std::vector<Permutation> locations;

	Permutation generatePermutation(unsigned const int &n);
	void readData( const std::string filename );
	int getCost(const Permutation &perm );
	int updateCost(const Permutation &, const Permutation &, unsigned const int& i, unsigned const int& j);
	std::pair<Permutation, int> randomSearch(unsigned const int &n, const double &time_seconds);
	std::pair<Permutation, int> randomWalk(unsigned const int &n, const double &time_seconds);
	std::pair<Permutation, int> localGreedy(unsigned const int &n);
	std::pair<Permutation, int> localSteepest(unsigned const int &n);
	std::pair<Permutation, int> heuristics(unsigned const int &n);

};