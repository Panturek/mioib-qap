#include <string>
#include <vector>
#include "utils.hpp"

class QAP{
	int cost;

public:
	std::vector<Permutation> facilities;
	std::vector<Permutation> locations;

	Permutation generatePermutation(unsigned const int &n);
	void readData( const std::string filename );
	int getCost(const Permutation &perm );
	int updateCost(const Permutation &, const Permutation &, unsigned const int& i, unsigned const int& j);
	double findTemp();
	std::tuple<Permutation, int> randomSearch(unsigned const int &n, const double &time_seconds);
	std::tuple<Permutation, int> randomWalk(unsigned const int &n, const double &time_seconds);
	std::tuple<Permutation, int, int> localGreedy(unsigned const int &n);
	std::tuple<Permutation, int, int> localSteepest(unsigned const int &n);
	Permutation heuristics(unsigned const int &n);
	std::tuple<Permutation, int, int> simmulatedAnnealing(unsigned const int &n, const double &temp);
	std::tuple<Permutation, int, int> tabu(unsigned const int &n);
};